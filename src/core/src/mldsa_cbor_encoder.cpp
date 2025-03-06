#include <openssl/core_dispatch.h>
#include <openssl/core_names.h>
#include <openssl/evp.h>
#include <openssl/params.h>
#include <string.h>
#include <zcbor_encode.h>

#define CBOR_BUFFER_SIZE 512

typedef struct {
    int keytype;
} MLDSA_ENCODER_CTX;

static const struct {
    const char *name;
    const uint32_t oid[10];
    size_t oid_len;
} mldsa_oids[] = {
    {"mldsa44", {2, 16, 840, 1, 101, 3, 4, 3, 17}, 9},
    {"mldsa65", {2, 16, 840, 1, 101, 3, 4, 3, 18}, 9},
    {"mldsa87", {2, 16, 840, 1, 101, 3, 4, 3, 19}, 9},
    {"mldsa44_ed25519", {2, 16, 840, 1, 114027, 80, 8, 1, 3}, 10},
    {"mldsa44_p256", {2, 16, 840, 1, 114027, 80, 8, 1, 4}, 10},
    {"mldsa65_ed25519", {2, 16, 840, 1, 114027, 80, 8, 1, 10}, 10},
    {"mldsa65_p256", {2, 16, 840, 1, 114027, 80, 8, 1, 8}, 10},
    {"mldsa65_bp256", {2, 16, 840, 1, 114027, 80, 8, 1, 9}, 10},
    {"mldsa87_ed448", {2, 16, 840, 1, 114027, 80, 8, 1, 13}, 10},
    {"mldsa87_p384", {2, 16, 840, 1, 114027, 80, 8, 1, 11}, 10},
    {"mldsa87_bp384", {2, 16, 840, 1, 114027, 80, 8, 1, 12}, 10}
};

// Initialize encoder context
static void *mldsa_encoder_newctx(void *provctx) {
    MLDSA_ENCODER_CTX *ctx = (MLDSA_ENCODER_CTX *) OPENSSL_zalloc(sizeof(*ctx));
    if (!ctx) return NULL;
    return ctx;
}

// Free encoder context
static void mldsa_encoder_freectx(void *ctx) {
    OPENSSL_free(ctx);
}

// Convert an MLDSA key to CBOR format using `zcbor`
static int mldsa_encoder_encode(void *ctx, OSSL_CORE_BIO *out, const void *key,
                                int selection, OSSL_PASSPHRASE_CALLBACK *cb, void *cbarg) {
    const EVP_PKEY *pkey = (const EVP_PKEY *)key;
    if (!pkey) return 0;

    size_t privkey_len = 0, pubkey_len = 0;
    uint8_t privkey[512], pubkey[512];

    // Extract raw private and public key bytes
    if (selection & OSSL_KEYMGMT_SELECT_PRIVATE_KEY) {
        if (!EVP_PKEY_get_raw_private_key(pkey, privkey, &privkey_len))
            return 0;
    }
    if (selection & OSSL_KEYMGMT_SELECT_PUBLIC_KEY) {
        if (!EVP_PKEY_get_raw_public_key(pkey, pubkey, &pubkey_len))
            return 0;
    }

    // CBOR encoding using zcbor
    uint8_t cbor_buffer[CBOR_BUFFER_SIZE];
    struct zcbor_state zs = ZCBOR_STATE_INIT(cbor_buffer, sizeof(cbor_buffer));

    if (!zcbor_map_start_encode(&zs, 3)) {
        return 0;
    }

    // Encode OID as CBOR array
    if (!zcbor_tstr_put_term(&zs, "oid") ||
        !zcbor_list_start_encode(&zs, 10)) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!zcbor_uint32_put(&zs, mldsa_oids[i].oid[i])) {
            return 0;
        }
    }
    if (!zcbor_list_end_encode(&zs, 10)) {
        return 0;
    }

    // Add public key
    if (selection & OSSL_KEYMGMT_SELECT_PUBLIC_KEY) {
        if (!zcbor_tstr_put_term(&zs, "publicKey") ||
            !zcbor_bstr_encode_ptr(&zs, pubkey, pubkey_len)) {
            return 0;
        }
    }

    // Add private key
    if (selection & OSSL_KEYMGMT_SELECT_PRIVATE_KEY) {
        if (!zcbor_tstr_put_term(&zs, "privateKey") ||
            !zcbor_bstr_encode_ptr(&zs, privkey, privkey_len)) {
            return 0;
        }
    }

    if (!zcbor_map_end_encode(&zs, 3)) {
        return 0;
    }

    // Write CBOR data to OpenSSL BIO
    BIO_write((BIO *)out, cbor_buffer, zs.offset);

    return 1;
}

// Define encoder functions
static const OSSL_DISPATCH mldsa_encoder_functions[] = {
    { OSSL_FUNC_ENCODER_NEWCTX, (void (*)(void))mldsa_encoder_newctx },
    { OSSL_FUNC_ENCODER_FREECTX, (void (*)(void))mldsa_encoder_freectx },
    { OSSL_FUNC_ENCODER_ENCODE, (void (*)(void))mldsa_encoder_encode },
    { 0, NULL }
};

// Provider entry point
static const OSSL_ALGORITHM mldsa_encoders[] = {
    { "MLDSA-CBOR", "provider=mldsa", mldsa_encoder_functions },
    { NULL, NULL, NULL }
};

static const OSSL_ALGORITHM *mldsa_provider_query(void *provctx, int operation_id, int *no_cache) {
    if (operation_id == OSSL_OP_ENCODER)
        return mldsa_encoders;
    return NULL;
}

static const OSSL_DISPATCH mldsa_provider_functions[] = {
    { OSSL_FUNC_PROVIDER_QUERY_OPERATION, (void (*)(void))mldsa_provider_query },
    { 0, NULL }
};

// OpenSSL provider initialization function
int OSSL_provider_init(const OSSL_CORE_HANDLE *handle, const OSSL_DISPATCH *in,
                       const OSSL_DISPATCH **out, void **provctx) {
    *out = mldsa_provider_functions;
    return 1;
}
