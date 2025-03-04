#ifndef C509_CRYPTO_H
#define C509_CRYPTO_H

#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <openssl/evp.h>
#include <openssl/core_names.h>

#define OQSPROV_PROPQ "provider=oqsprovider"

extern "C" {
OSSL_provider_init_fn oqs_provider_init;
}

OSSL_LIB_CTX *load_oqs_provider();

#endif // C509_CRYPTO_H