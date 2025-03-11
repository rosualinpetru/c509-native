#include "util/codec_internal.hpp"

#define ZCBOR_STATES_CERT 15 // TODO
#define ZCBOR_STATES_PRIV 15 // TODO
#define ZCBOR_STATES_COSE_C509 15 // TODO
#define ZCBOR_STATES_PEM 15 // TODO
#define ZCBOR_STATES_CSR 15 // TODO
#define ZCBOR_STATES_CRL 15 // TODO

#define ZCBOR_ENTRY_CODEC_IMPL(Type, States)                                                          \
    int cbor_encode(uint8_t *payload, size_t payload_len, const Type *input, size_t *payload_len_out) \
    {                                                                                                 \
        zcbor_state_t states[States];                                                                 \
        return zcbor_entry_function(                                                                  \
            payload,                                                                                  \
            payload_len,                                                                              \
            (void *)input,                                                                            \
            payload_len_out,                                                                          \
            states,                                                                                   \
            (zcbor_decoder_t *)CBORCodec<Type>::encode,                                               \
            sizeof(states) / sizeof(zcbor_state_t),                                                   \
            1);                                                                                       \
    }                                                                                                 \
                                                                                                      \
    int cbor_decode(const uint8_t *payload, size_t payload_len, Type *result, size_t *payload_len_out) \
    {                                                                                                  \
        zcbor_state_t states[States];                                                                  \
        return zcbor_entry_function(                                                                   \
            payload,                                                                                   \
            payload_len,                                                                               \
            (void *)result,                                                                            \
            payload_len_out,                                                                           \
            states,                                                                                    \
            (zcbor_decoder_t *)CBORCodec<Type>::decode,                                                \
            sizeof(states) / sizeof(zcbor_state_t),                                                    \
            1);                                                                                        \
    }

namespace C509 {
    ZCBOR_ENTRY_CODEC_IMPL(COSE_C509, ZCBOR_STATES_COSE_C509)

    ZCBOR_ENTRY_CODEC_IMPL(TBSCertificate, ZCBOR_STATES_CERT)

    ZCBOR_ENTRY_CODEC_IMPL(C509Certificate, ZCBOR_STATES_CERT)

    ZCBOR_ENTRY_CODEC_IMPL(C509PrivateKey, ZCBOR_STATES_PRIV)

    ZCBOR_ENTRY_CODEC_IMPL(C509PEM, ZCBOR_STATES_PEM)

    namespace CSR {
        ZCBOR_ENTRY_CODEC_IMPL(TBSCertificateRequest, ZCBOR_STATES_CSR)

        ZCBOR_ENTRY_CODEC_IMPL(C509CertificateRequest, ZCBOR_STATES_CSR)
    }

    namespace CRL {
        ZCBOR_ENTRY_CODEC_IMPL(C509CertificateRevocationList, ZCBOR_STATES_CRL)

        ZCBOR_ENTRY_CODEC_IMPL(TBSCertificateRevocationList, ZCBOR_STATES_CRL)
    }
}
