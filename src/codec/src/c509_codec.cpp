#include "c509_codec_internal.hpp"

#define ZCBOR_STATES 15

namespace C509
{
    int encode(uint8_t *payload, size_t payload_len, const C509Certificate *input, size_t *payload_len_out)
    {
        zcbor_state_t states[ZCBOR_STATES];

        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)input,
            payload_len_out,
            states,
            (zcbor_decoder_t *)CBORCodec<C509Certificate>::encode_unwrapped,
            sizeof(states) / sizeof(zcbor_state_t),
            1);
    }

    int decode(const uint8_t *payload, size_t payload_len, C509Certificate *result, size_t *payload_len_out)
    {
        zcbor_state_t states[ZCBOR_STATES];

        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)result,
            payload_len_out,
            states,
            (zcbor_decoder_t *)CBORCodec<C509Certificate>::decode_unwrapped,
            sizeof(states) / sizeof(zcbor_state_t),
            1);
    }
}
