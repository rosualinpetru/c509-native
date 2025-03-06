#include <iostream>

#include "c509_core/c509.hpp"
#include "c509_crypto/crypto.hpp"
#include "c509_codec/codec.hpp"

bool verify_csr(const uint8_t *csr, const size_t csr_size) {
    if (!csr || csr_size == 0) {
        std::cerr << "Error: Invalid CSR input.\n";
        return false;
    }

    C509::CSR::C509CertificateRequest request{};
    if (cbor_decode(csr, csr_size, &request, nullptr) != 0) {
        std::cerr << "Error: Failed to decode CSR.\n";
        return false;
    }

    std::string algorithm_name;
    if (!map_id_to_alg(algorithm_name, request.tbs_certificate_request.subject_signature_algorithm)) {
        std::cerr << "Error: Unknown algorithm.\n";
        return false;
    }

    OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
    if (!oqs_provider_ctx) {
        std::cerr << "Error: Failed to load OQS provider.\n";
        return false;
    }

    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm_name.c_str(), OQSPROV_PROPQ);
    if (!pkey_ctx) {
        std::cerr << "Error: Failed to create EVP_PKEY_CTX for " << algorithm_name << "\n";
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY *public_key = nullptr;
    if (EVP_PKEY_fromdata_init(pkey_ctx) <= 0) {
        std::cerr << "Error: Failed to initialize EVP_PKEY_fromdata.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    OSSL_PARAM params[] = {
        OSSL_PARAM_construct_octet_string(OSSL_PKEY_PARAM_PUB_KEY,
                                          request.tbs_certificate_request.subject_public_key.bytes.data_p(),
                                          *request.tbs_certificate_request.subject_public_key.bytes.len_p()),
        OSSL_PARAM_construct_end()
    };

    if (EVP_PKEY_fromdata(pkey_ctx, &public_key, EVP_PKEY_PUBLIC_KEY, params) <= 0) {
        std::cerr << "Error: Failed to load public key from CSR.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    uint8_t tbs_buffer[MAX_BUFFER_SIZE];
    size_t tbs_buffer_size = sizeof(tbs_buffer);

    if (cbor_encode(tbs_buffer, MAX_BUFFER_SIZE, &request.tbs_certificate_request, &tbs_buffer_size) != 0) {
        std::cerr << "Error: Failed to encode TBSCertificateRequest.\n";
        EVP_PKEY_free(public_key);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY_CTX *verify_ctx = EVP_PKEY_CTX_new(public_key, nullptr);
    if (!verify_ctx) {
        std::cerr << "Error: Failed to create verification context.\n";
        EVP_PKEY_free(public_key);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    if (EVP_PKEY_verify_init(verify_ctx) <= 0) {
        std::cerr << "Error: EVP_PKEY_verify_init() failed.\n";
        EVP_PKEY_CTX_free(verify_ctx);
        EVP_PKEY_free(public_key);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    const int verify_result = EVP_PKEY_verify(
        verify_ctx,
        request.subject_signature_value.bytes.data_p(),
        *request.subject_signature_value.bytes.len_p(),
        tbs_buffer,
        tbs_buffer_size
    );

    EVP_PKEY_CTX_free(verify_ctx);
    EVP_PKEY_free(public_key);
    OSSL_LIB_CTX_free(oqs_provider_ctx);

    return verify_result > 0;
}
