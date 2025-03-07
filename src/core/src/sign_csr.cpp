#include <iostream>
#include <ctime>

#include "c509_core/c509.hpp"

#include "c509_crypto/crypto.hpp"
#include "c509_types/types.hpp"
#include "c509_codec/codec.hpp"

// Extremely simplified logic
bool sign_csr_impl(const uint8_t *csr, size_t csr_size, const uint8_t *private_key, size_t private_key_size,
                   C509::Name *issuer, uint32_t days, uint64_t serial_number,
                   uint8_t *cert_out, size_t &cert_out_size);

bool self_sign_csr(const uint8_t *csr, const size_t csr_size, const uint8_t *private_key, const size_t private_key_size,
                   const uint32_t days, const uint64_t serial_number, uint8_t *cert_out, size_t &cert_out_size) {
    return sign_csr_impl(csr, csr_size, private_key, private_key_size, nullptr, days, serial_number, cert_out,
                         cert_out_size);
}

bool sign_csr(const uint8_t *csr, size_t csr_size, const uint8_t *private_key, size_t private_key_size,
              const uint8_t *ca_cert, size_t ca_cert_size, uint32_t days, uint64_t serial_number,
              uint8_t *cert_out, size_t &cert_out_size) {
    if (!ca_cert || ca_cert_size == 0) {
        std::cerr << "Error: Invalid input.\n";
        return false;
    }

    C509::C509Certificate c509_ca_cert{};
    if (cbor_decode(ca_cert, ca_cert_size, &c509_ca_cert, nullptr) != 0) {
        std::cerr << "Error: Failed to parse ca cert.\n";
        return false;
    }

    return sign_csr_impl(csr, csr_size, private_key, private_key_size, &c509_ca_cert.tbs_certificate.subject, days,
                         serial_number, cert_out,
                         cert_out_size);
}

void set_validity_period(C509::Time &not_before, C509::Time &not_after, const uint32_t days) {
    const std::time_t current_time = std::time(nullptr);
    not_before.epoch_seconds = static_cast<uint64_t>(current_time);
    const std::time_t expiration_time = current_time + (days * 24 * 60 * 60);
    not_after.epoch_seconds = static_cast<uint64_t>(expiration_time);
}

bool sign_csr_impl(const uint8_t *csr, size_t csr_size, const uint8_t *private_key, size_t private_key_size,
                   C509::Name *issuer, uint32_t days, uint64_t serial_number,
                   uint8_t *cert_out, size_t &cert_out_size) {
    if (!csr || csr_size == 0 || !private_key || private_key_size == 0) {
        std::cerr << "Error: Invalid input.\n";
        return false;
    }

    C509::CSR::C509CertificateRequest request{};
    if (cbor_decode(csr, csr_size, &request, nullptr) != 0) {
        std::cerr << "Error: Failed to parse CSR.\n";
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

    // Construct the self-signed certificate
    C509::C509Certificate cert{};
    auto &tbs = cert.tbs_certificate;

    tbs.c509_certificate_type = 2;

    tbs.certificate_serial_number.bytes.copy(reinterpret_cast<const unsigned char *>(&serial_number),
                                             sizeof(serial_number));

    if (issuer != nullptr)
        tbs.issuer.emplace(*issuer);
    else
        tbs.issuer.reset();

    tbs.subject = request.tbs_certificate_request.subject;
    tbs.subject_public_key = request.tbs_certificate_request.subject_public_key;
    tbs.subject_public_key_algorithm = request.tbs_certificate_request.subject_public_key_algorithm;
    tbs.issuer_signature_algorithm = request.tbs_certificate_request.subject_signature_algorithm;
    tbs.extensions = request.tbs_certificate_request.extensions_request;
    set_validity_period(tbs.validity_not_before, tbs.validity_not_after.get(), days);
    tbs.validity_not_after.set_has();

    // Encode TBS certificate for signing
    uint8_t tbs_buffer[MAX_BUFFER_SIZE];
    size_t tbs_buffer_size;
    if (cbor_encode(tbs_buffer, MAX_BUFFER_SIZE, &tbs, &tbs_buffer_size) != 0) {
        std::cerr << "Failed to encode TBSCertificate.\n";
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

    *cert.signature_value.bytes.len_p() = cert.signature_value.bytes.capacity();
    if (EVP_PKEY_sign(sign_ctx, cert.signature_value.bytes.data_p(),
                      cert.signature_value.bytes.len_p(), tbs_buffer, tbs_buffer_size) <= 0) {
        std::cerr << "Failed to sign TBSCertificate.\n";
        return false;
    }

    // Encode the self-signed certificate
    if (cbor_encode(cert_out, cert_out_size, &cert, &cert_out_size) != 0) {
        std::cerr << "Failed to encode C509Certificate.\n";
        return false;
    }

    // Cleanup
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(sign_ctx);
    EVP_PKEY_CTX_free(pkey_ctx);
    OSSL_LIB_CTX_free(oqs_provider_ctx);

    return true;
}
