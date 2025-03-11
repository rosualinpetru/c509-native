#include <iostream>

#include "c509_core/c509.hpp"

#include "c509_crypto/crypto.hpp"
#include "c509_types/types.hpp"
#include "c509_codec/codec.hpp"

bool key_gen(const std::string &algorithm, uint8_t *private_key_out, size_t &private_key_out_size) {
    OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
    if (!oqs_provider_ctx) {
        std::cerr << "Error: Failed to load OQS provider.\n";
        return false;
    }

    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm.c_str(), OQSPROV_PROPQ);
    if (!pkey_ctx) {
        std::cerr << "Error: Failed to create EVP_PKEY_CTX for algorithm " << algorithm << ".\n";
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    if (EVP_PKEY_keygen_init(pkey_ctx) <= 0) {
        std::cerr << "Error: Failed to initialize key generation.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY *key = nullptr;
    if (EVP_PKEY_generate(pkey_ctx, &key) <= 0) {
        std::cerr << "Error: Failed to generate composite key.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    C509::C509PrivateKey private_key{};

    if (!map_alg_to_id(algorithm, private_key.subject_private_key_algorithm)) {
        std::cerr << "Error: Failed to map algorithm to identifier.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    C509::PrivateKey *priv_k = &private_key.subject_private_key_info.private_key;
    *priv_k->bytes.len_p() = priv_k->bytes.capacity();
    if (EVP_PKEY_get_raw_private_key(key, priv_k->bytes.data_p(), priv_k->bytes.len_p()) <= 0) {
        std::cerr << "Error: Failed to extract private key - might not fit buffer.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    C509::PublicKey *pk = &private_key.subject_private_key_info.public_key;
    *pk->bytes.len_p() = pk->bytes.capacity();
    if (EVP_PKEY_get_raw_public_key(key, pk->bytes.data_p(), pk->bytes.len_p()) <= 0) {
        std::cerr << "Error: Failed to extract private key - might not fit buffer.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    if (cbor_encode(private_key_out, private_key_out_size, &private_key, &private_key_out_size) != 0) {
        std::cerr << "Error: Failed to encode C509CertificateRequest.\n";
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
        return false;
    }

    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(pkey_ctx);
    OSSL_LIB_CTX_free(oqs_provider_ctx);

    return true;
}
