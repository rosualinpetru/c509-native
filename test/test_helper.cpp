#include <cstddef>

#include "c509_codec_internal.hpp"

template <typename T, size_t S>
struct CodecTestHelper
{
    static int encode(uint8_t *payload, size_t payload_len, const T *input, size_t *payload_len_out)
    {
        zcbor_state_t state[S];

        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)input,
            payload_len_out,
            state,
            (zcbor_decoder_t *)C509::CBORCodec<T>::encode,
            sizeof(state) / sizeof(zcbor_state_t),
            1);
    }

    static int decode(const uint8_t *payload, size_t payload_len, T *result, size_t *payload_len_out)
    {
        zcbor_state_t state[S];

        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)result,
            payload_len_out,
            state,
            (zcbor_decoder_t *)C509::CBORCodec<T>::decode,
            sizeof(state) / sizeof(zcbor_state_t),
            1);
    }
};