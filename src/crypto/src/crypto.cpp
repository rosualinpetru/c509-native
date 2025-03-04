#include <iostream>

#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <openssl/evp.h>

#include "c509_crypto/crypto.hpp"

static auto kOQSProviderName = "oqsprovider";

OSSL_LIB_CTX *load_oqs_provider() {
    OSSL_LIB_CTX *libctx = OSSL_LIB_CTX_new();
    if (!libctx) {
        std::cerr << "Failed to create a new OpenSSL library context.\n";
        return nullptr;
    }

    int ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 0) {
        std::cerr << "OSSL_PROVIDER_available returned " << ret << ", but 0 was expected.\n";
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    ret = OSSL_PROVIDER_add_builtin(libctx, kOQSProviderName, oqs_provider_init);
    if (ret != 1) {
        std::cerr << "OSSL_PROVIDER_add_builtin failed with return code " << ret << "\n";
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    OSSL_PROVIDER *provider = OSSL_PROVIDER_load(libctx, kOQSProviderName);
    if (!provider) {
        std::cerr << "OSSL_PROVIDER_load failed.\n";
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 1) {
        std::cerr << "OSSL_PROVIDER_available returned " << ret << ", but 1 was expected.\n";
        OSSL_PROVIDER_unload(provider);
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    ret = OSSL_PROVIDER_self_test(provider);
    if (ret != 1) {
        std::cerr << "OSSL_PROVIDER_self_test failed with return code " << ret << "\n";
        OSSL_PROVIDER_unload(provider);
        OSSL_LIB_CTX_free(libctx);
        return nullptr;
    }

    return libctx;
}
