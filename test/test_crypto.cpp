#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <openssl/evp.h>
#include <openssl/core_names.h>

#define OQSPROV_PROPQ "provider=oqsprovider"

extern "C"
{
    OSSL_provider_init_fn oqs_provider_init;
}

static const char *kOQSProviderName = "oqsprovider";

OSSL_LIB_CTX *load_oqs_provider()
{
    OSSL_LIB_CTX *libctx = OSSL_LIB_CTX_new();
    if (!libctx)
    {
        std::cerr << "Failed to create a new OpenSSL library context.\n";
        return nullptr;
    }

    int ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 0)
    {
        std::cerr << "OSSL_PROVIDER_available returned " << ret << ", but 0 was expected.\n";
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    ret = OSSL_PROVIDER_add_builtin(libctx, kOQSProviderName, oqs_provider_init);
    if (ret != 1)
    {
        std::cerr << "OSSL_PROVIDER_add_builtin failed with return code " << ret << "\n";
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    OSSL_PROVIDER *provider = OSSL_PROVIDER_load(libctx, kOQSProviderName);
    if (!provider)
    {
        std::cerr << "OSSL_PROVIDER_load failed.\n";
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 1)
    {
        std::cerr << "OSSL_PROVIDER_available returned " << ret << ", but 1 was expected.\n";
        OSSL_PROVIDER_unload(provider);
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    ret = OSSL_PROVIDER_self_test(provider);
    if (ret != 1)
    {
        std::cerr << "OSSL_PROVIDER_self_test failed with return code " << ret << "\n";
        OSSL_PROVIDER_unload(provider);
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    return libctx;
}

void print_key_bytes(EVP_PKEY *key)
{
    size_t keylen = 0;
    unsigned char *keydata = nullptr;

    // Extract raw public key bytes
    if (EVP_PKEY_get_octet_string_param(key, OSSL_PKEY_PARAM_PUB_KEY, nullptr, 0, &keylen))
    {
        keydata = new unsigned char[keylen];
        if (EVP_PKEY_get_octet_string_param(key, OSSL_PKEY_PARAM_PUB_KEY, keydata, keylen, &keylen))
        {
            std::cout << "Public Key (" << keylen << " bytes): ";
            for (size_t i = 0; i < keylen; i++)
            {
                printf("%02X", keydata[i]);
            }
            std::cout << std::endl;
        }
        delete[] keydata;
    }
}

TEST_CASE("Gen Composite Key")
{
    OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
    if (!oqs_provider_ctx)
    {
        std::cerr << "Failed to load OQS provider.\n";
        return;
    }

    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, "mldsa44_ed25519", OQSPROV_PROPQ);
    if (!pkey_ctx)
    {
        std::cerr << "Failed to create EVP_PKEY_CTX.\n";
        return;
    }

    if (EVP_PKEY_keygen_init(pkey_ctx) <= 0)
    {
        std::cerr << "Failed to initialize key generation.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        return;
    }

    EVP_PKEY *key = nullptr;
    if (EVP_PKEY_generate(pkey_ctx, &key) <= 0)
    {
        std::cerr << "Failed to generate composite key.\n";
        EVP_PKEY_CTX_free(pkey_ctx);
        return;
    }

    // Print Key in Hexadecimal
    print_key_bytes(key);

    const char *key_alg = EVP_PKEY_get0_type_name(key);
    printf("Key Algorithm: %s\n", key_alg);

    // Cleanup
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(pkey_ctx);
    OSSL_LIB_CTX_free(oqs_provider_ctx);
}
