#include "util/codec_internal.hpp"

// TODO
#define ZCBOR_STATES_CERT 15
// TODO
#define ZCBOR_STATES_CSR 15
// TODO
#define ZCBOR_STATES_CRL 15

#define ZCBOR_ENTRY_ENCODE_IMPL(Type, States)                                                    \
    int encode(uint8_t *payload, size_t payload_len, const Type *input, size_t *payload_len_out) \
    {                                                                                            \
        zcbor_state_t states[States];                                                            \
        return zcbor_entry_function(                                                             \
            payload,                                                                             \
            payload_len,                                                                         \
            (void *)input,                                                                       \
            payload_len_out,                                                                     \
            states,                                                                              \
            (zcbor_decoder_t *)CBORCodec<Type>::encode,                                          \
            sizeof(states) / sizeof(zcbor_state_t),                                              \
            1);                                                                                  \
    }

#define ZCBOR_ENTRY_DECODE_IMPL(Type, States)                                                     \
    int decode(const uint8_t *payload, size_t payload_len, Type *result, size_t *payload_len_out) \
    {                                                                                             \
        zcbor_state_t states[States];                                                             \
        return zcbor_entry_function(                                                              \
            payload,                                                                              \
            payload_len,                                                                          \
            (void *)result,                                                                       \
            payload_len_out,                                                                      \
            states,                                                                               \
            (zcbor_decoder_t *)CBORCodec<Type>::decode,                                           \
            sizeof(states) / sizeof(zcbor_state_t),                                               \
            1);                                                                                   \
    }

namespace C509
{

    ZCBOR_ENTRY_ENCODE_IMPL(C509Certificate, ZCBOR_STATES_CERT)
    ZCBOR_ENTRY_DECODE_IMPL(C509Certificate, ZCBOR_STATES_CERT)

    namespace CSR
    {
        ZCBOR_ENTRY_ENCODE_IMPL(C509CertificateRequest, ZCBOR_STATES_CSR)
        ZCBOR_ENTRY_DECODE_IMPL(C509CertificateRequest, ZCBOR_STATES_CSR)
    }

    namespace CRL
    {
        ZCBOR_ENTRY_ENCODE_IMPL(C509CertificateRevocationList, ZCBOR_STATES_CRL)
        ZCBOR_ENTRY_DECODE_IMPL(C509CertificateRevocationList, ZCBOR_STATES_CRL)
    }
}
