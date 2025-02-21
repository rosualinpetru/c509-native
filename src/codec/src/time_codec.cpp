#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<Time>::encode_unwrapped(zcbor_state_t *state, const Time &input)
{
    if (!zcbor_uint64_put(state, input.epochSeconds))
        ZCBOR_ERR(C509_ERR_TIME_ENC_INT);

    return true;
}

bool CBORCodec<Time>::decode_unwrapped(zcbor_state_t *state, Time &output)
{
    uint64_t epoch_value;

    if (!zcbor_uint64_decode(state, &epoch_value))
        ZCBOR_ERR(C509_ERR_TIME_DEC_INT);

    output.epochSeconds = epoch_value;
    return true;
}