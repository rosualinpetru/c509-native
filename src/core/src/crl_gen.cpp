#include <iostream>
#include <ctime>

#include "c509_core/c509.hpp"

#include "c509_crypto/crypto.hpp"
#include "c509_types/types.hpp"
#include "c509_codec/codec.hpp"

bool crl_gen(const uint8_t *private_key, size_t private_key_size,
             const uint8_t *ca_cert, size_t ca_cert_size,
             uint32_t days,
             uint8_t *crl_out, size_t &crl_out_size) {
    if (!ca_cert || ca_cert_size == 0 || !private_key || private_key_size == 0) {
        std::cerr << "Error: Invalid input.\n";
        return false;
    }

    C509::C509Certificate cert{};
    if (cbor_decode(ca_cert, ca_cert_size, &cert, nullptr) != 0) {
        std::cerr << "Error: Failed to parse CA cert.\n";
        return false;
    }

    C509::C509PrivateKey c509_private_key{};
    if (cbor_decode(private_key, private_key_size, &c509_private_key, nullptr) != 0) {
        std::cerr << "Error: Failed to parse private key.\n";
        return false;
    }


    // Construct the CRL
    C509::CRL::C509CertificateRevocationList crl{};
    auto &tbs = crl.tbs_certificate_revocation_list;

    tbs.c509_certificate_revocation_list_type = 0; // TODO: Value not currently specified in the draft
    tbs.issuer = cert.tbs_certificate.subject;
    tbs.issuer_signature_algorithm = c509_private_key.subject_private_key_algorithm;
    tbs.crl_extensions.type = C509::Extensions::Type::List;
    tbs.crl_extensions.extensions.clear();
    tbs.revoked_certificates.clear();
    tbs.this_update.epoch_seconds = static_cast<uint64_t>(std::time(nullptr));
    tbs.next_update.epoch_seconds = tbs.this_update.epoch_seconds + days * 24 * 60 * 60;

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

    // Reconstruct Private Key
    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm_name.c_str(), OQSPROV_PROPQ);
    if (!pkey_ctx) {
        std::cerr << "Error: Failed to create EVP_PKEY_CTX.\n";
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY *key = nullptr;
    OSSL_PARAM params[] = {
        OSSL_PARAM_construct_octet_string(
            OSSL_PKEY_PARAM_PRIV_KEY, c509_private_key.subject_private_key_info.private_key.bytes.data_p(),
            c509_private_key.subject_private_key_info.private_key.bytes.size()),
        OSSL_PARAM_construct_octet_string(
            OSSL_PKEY_PARAM_PUB_KEY, c509_private_key.subject_private_key_info.public_key.bytes.data_p(),
            c509_private_key.subject_private_key_info.public_key.bytes.size()),
        OSSL_PARAM_construct_end()
    };

    if (EVP_PKEY_fromdata_init(pkey_ctx) <= 0 || EVP_PKEY_fromdata(pkey_ctx, &key, EVP_PKEY_KEYPAIR, params) <= 0) {
        std::cerr << "Error: Failed to reconstruct private key.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    // Encode TBS certificate for signing
    uint8_t tbs_buffer[MAX_BUFFER_SIZE];
    size_t tbs_buffer_size;
    if (cbor_encode(tbs_buffer, MAX_BUFFER_SIZE, &tbs, &tbs_buffer_size) != 0) {
        std::cerr << "Error: Failed to encode C509CertificateRevocationList.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    // Sign the TBS certificate
    EVP_PKEY_CTX *sign_ctx = EVP_PKEY_CTX_new(key, nullptr);
    if (!sign_ctx || EVP_PKEY_sign_init(sign_ctx) <= 0) {
        std::cerr << "Error: Signing context setup failed.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(sign_ctx);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    *crl.issuer_signature_value.bytes.len_p() = crl.issuer_signature_value.bytes.capacity();
    if (EVP_PKEY_sign(sign_ctx, crl.issuer_signature_value.bytes.data_p(),
                      crl.issuer_signature_value.bytes.len_p(), tbs_buffer, tbs_buffer_size) <= 0) {
        std::cerr << "Error: Failed to sign TBSCertificateRevocationList.\n";
        return false;
    }

    // Encode the self-signed certificate
    if (cbor_encode(crl_out, crl_out_size, &crl, &crl_out_size) != 0) {
        std::cerr << "Error: Failed to encode C509CertificateRevocationList.\n";
        return false;
    }

    // Cleanup
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(sign_ctx);
    EVP_PKEY_CTX_free(pkey_ctx);
    OSSL_LIB_CTX_free(oqs_provider_ctx);

    return true;
}
