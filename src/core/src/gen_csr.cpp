#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "c509_core/c509.hpp"
#include "c509_crypto/crypto.hpp"
#include "c509_codec/codec.hpp"

bool gen_csr(const uint8_t *private_key, size_t private_key_size,
             std::map<uint32_t, std::string> &subject_attributes,
             std::map<std::vector<uint32_t>, std::tuple<bool, std::string> > &extensions,
             uint8_t *csr_out, size_t &csr_out_size) {
    if (!private_key || private_key_size == 0) {
        std::cerr << "Error: Invalid private key input.\n";
        return false;
    }

    C509::C509PrivateKey c509_private_key{};
    if (cbor_decode(private_key, private_key_size, &c509_private_key, nullptr) != 0) {
        std::cerr << "Error: Failed to parse private key.\n";
        return false;
    }

    std::string algorithm_name;
    if (!map_id_to_alg(algorithm_name, c509_private_key.subject_private_key_algorithm)) {
        std::cerr << "Error: Unknown algorithm.\n";
        return false;
    }

    OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
    if (!oqs_provider_ctx) {
        std::cerr << "Error: Failed to load OQS provider.\n";
        return false;
    }

    // 🔹 Reconstruct Private Key in OpenSSL
    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm_name.c_str(), OQSPROV_PROPQ);
    if (!pkey_ctx) {
        std::cerr << "Error: Failed to create EVP_PKEY_CTX.\n";
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY *key = nullptr;
    OSSL_PARAM params[] = {
        OSSL_PARAM_construct_octet_string(OSSL_PKEY_PARAM_PRIV_KEY, c509_private_key.subject_private_key.data_p(),
                                          c509_private_key.subject_private_key.size()),
        OSSL_PARAM_construct_octet_string(OSSL_PKEY_PARAM_PUB_KEY, c509_private_key.subject_public_key.data_p(),
                                  c509_private_key.subject_public_key.size()),
        OSSL_PARAM_construct_end()
    };

    if (EVP_PKEY_fromdata_init(pkey_ctx) <= 0 || EVP_PKEY_fromdata(pkey_ctx, &key, EVP_PKEY_KEYPAIR, params) <= 0) {
        std::cerr << "Error: Failed to reconstruct private key.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    C509::CSR::C509CertificateRequest request{};
    auto &tbs = request.tbs_certificate_request;

    if (!map_alg_to_id(algorithm_name, tbs.subject_public_key_algorithm) || !map_alg_to_id(
            algorithm_name, tbs.subject_signature_algorithm)) {
        std::cerr << "Error: Failed map algorithm to identifier.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    auto &subject = tbs.subject;
    subject.type = C509::Name::Type::Attributes;
    *subject.attributes.len_p() = subject_attributes.size();

    if (!subject_attributes.empty()) {
        size_t index = 0;
        for (const auto &[type, value]: subject_attributes) {
            subject.attributes[index].type = C509::Attribute::Type::Int;
            subject.attributes[index].intAttribute.attribute_type = type;
            subject.attributes[index].intAttribute.attribute_value.copy(
                reinterpret_cast<const unsigned char *>(value.data()), value.size());
            index++;
        }
    } else {
        std::cerr << "Error: Empty subject.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    *tbs.subject_public_key.bytes.len_p() = tbs.subject_public_key.bytes.capacity();
    if (EVP_PKEY_get_raw_public_key(key, tbs.subject_public_key.bytes.data_p(),
                                    tbs.subject_public_key.bytes.len_p()) <= 0) {
        std::cerr << "Failed to extract public key - might not fit buffer.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    auto &ext_list = tbs.extensions_request;
    ext_list.type = C509::Extensions::Type::List;
    *ext_list.extensions.len_p() = extensions.size();

    if (!extensions.empty()) {
        size_t index = 0;
        for (const auto &[oid, ext_data]: extensions) {
            bool critical = std::get<0>(ext_data);
            const std::string &value = std::get<1>(ext_data);

            ext_list.extensions[index].type = C509::Extension::Type::OID;
            ext_list.extensions[index].oidExtension.extension_id.subids.copy(oid.data(), oid.size());
            ext_list.extensions[index].oidExtension.critical = critical;
            ext_list.extensions[index].oidExtension.extension_value.copy(
                reinterpret_cast<const unsigned char *>(value.data()), value.size());
            index++;
        }
    }

    uint8_t buffer[MAX_BUFFER_SIZE];
    size_t buffer_size;
    if (cbor_encode(buffer, MAX_BUFFER_SIZE, &tbs, &buffer_size) != 0) {
        std::cerr << "Error: Failed to encode TBSCertificateRequest.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY_CTX *sign_ctx = EVP_PKEY_CTX_new(key, nullptr);
    if (!sign_ctx || EVP_PKEY_sign_init(sign_ctx) <= 0) {
        std::cerr << "Error: Signing context setup failed.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(sign_ctx);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    *request.subject_signature_value.bytes.len_p() = request.subject_signature_value.bytes.capacity();
    if (EVP_PKEY_sign(sign_ctx, request.subject_signature_value.bytes.data_p(),
                      request.subject_signature_value.bytes.len_p(), buffer, buffer_size) <= 0) {
        std::cerr << "Error: Failed to sign TBSCertificateRequest.\n";
        return false;
    }

    if (cbor_encode(csr_out, csr_out_size, &request, &csr_out_size) != 0) {
        std::cerr << "Error: Failed to encode C509CertificateRequest.\n";
        return false;
    }

    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(sign_ctx);
    EVP_PKEY_CTX_free(pkey_ctx);
    OSSL_LIB_CTX_free(oqs_provider_ctx);

    return true;
}
