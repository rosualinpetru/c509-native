#include "c509_codec_internal.hpp"

namespace C509
{
    int encode(uint8_t *payload, size_t payload_len, const Certificate *input, size_t *payload_len_out)
    {
        zcbor_state_t states[13];

        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)input,
            payload_len_out,
            states,
            (zcbor_decoder_t *)CBORCodec<Certificate>::encode,
            sizeof(states) / sizeof(zcbor_state_t),
            1);
    }

    int decode(const uint8_t *payload, size_t payload_len, Certificate *result, size_t *payload_len_out)
    {
        zcbor_state_t states[13];

        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)result,
            payload_len_out,
            states,
            (zcbor_decoder_t *)CBORCodec<Certificate>::decode,
            sizeof(states) / sizeof(zcbor_state_t),
            2);
    }
}
