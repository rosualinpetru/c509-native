#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "c509_crypto/crypto.hpp"

void print_bytes(const char *label, const unsigned char *data, size_t len)
{
    std::cout << label << " " << len << ": ";
    for (size_t i = 0; i < len; i++)
        printf("%02X", data[i]);
    std::cout << std::endl;
}

TEST_CASE("Gen Composite Key")
{
    // Load OQS Provider
    OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
    if (!oqs_provider_ctx)
    {
        std::cerr << "Failed to load OQS provider.\n";
    }

    // Create keygen context
    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, "mldsa87_ed448", OQSPROV_PROPQ);
    if (!pkey_ctx)
    {
        std::cerr << "Failed to create EVP_PKEY_CTX.\n";
        OSSL_LIB_CTX_free(oqs_provider_ctx);
    }

    // Initialize keygen
    if (EVP_PKEY_keygen_init(pkey_ctx) <= 0)
    {
        std::cerr << "Failed to initialize key generation.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);
    }

    // Generate keypair
    EVP_PKEY *key = nullptr;
    if (EVP_PKEY_generate(pkey_ctx, &key) <= 0)
    {
        std::cerr << "Failed to generate composite key.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);

    }

    // Extract raw private key
    size_t priv_len = 0;
    EVP_PKEY_get_raw_private_key(key, nullptr, &priv_len);
    std::vector<unsigned char> priv_key(priv_len);
    if (EVP_PKEY_get_raw_private_key(key, priv_key.data(), &priv_len) > 0)
    {
        print_bytes("Private Key (Raw)", priv_key.data(), priv_len);
    }
    else
    {
        std::cerr << "Failed to extract raw private key.\n";
    }

    // Extract raw public key
    size_t pub_len = 0;
    EVP_PKEY_get_raw_public_key(key, nullptr, &pub_len);
    std::vector<unsigned char> pub_key(pub_len);
    if (EVP_PKEY_get_raw_public_key(key, pub_key.data(), &pub_len) > 0)
    {
        print_bytes("Public Key (Raw)", pub_key.data(), pub_len);
    }
    else
    {
        std::cerr << "Failed to extract raw public key.\n";
    }

    // Cleanup
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(pkey_ctx);
    OSSL_LIB_CTX_free(oqs_provider_ctx);

}