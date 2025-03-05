#include <iostream>

#include "c509_core/c509.hpp"

#include "c509_crypto/crypto.hpp"
#include "c509_types/types.hpp"
#include "c509_codec/codec.hpp"

#define MAX_BUFFER_SIZE 16384

namespace C509 {
    bool keygen(const std::string &algorithm,uint8_t *private_key_out,size_t &private_key_out_size) {
        OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
        if (!oqs_provider_ctx) {
            std::cerr << "Failed to load OQS provider.\n";
            return false;
        }

        EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm.c_str(), OQSPROV_PROPQ);
        if (!pkey_ctx) {
            std::cerr << "Failed to create EVP_PKEY_CTX for algorithm " << algorithm << ".\n";
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (EVP_PKEY_keygen_init(pkey_ctx) <= 0) {
            std::cerr << "Failed to initialize key generation.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        EVP_PKEY *key = nullptr;
        if (EVP_PKEY_generate(pkey_ctx, &key) <= 0) {
            std::cerr << "Failed to generate composite key.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        C509PrivateKey private_key{};

        if (!map_algid_to_oid(algorithm, private_key.subject_private_key_algorithm)) {
            std::cerr << "Failed to map algorithm to identifier.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        *private_key.subject_private_key.len_p() = private_key.subject_private_key.capacity();
        if (EVP_PKEY_get_raw_private_key(key, private_key.subject_private_key.data_p(),
                                         private_key.subject_private_key.len_p()) <= 0) {
            std::cerr << "Failed to extract private key - might not fit buffer.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (cbor_encode(private_key_out, private_key_out_size, &private_key, &private_key_out_size) != 0) {
            std::cerr << "Failed to encode C509CertificateRequest.\n";
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
}
