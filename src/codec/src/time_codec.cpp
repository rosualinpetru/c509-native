#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<Time>::encode_unwrapped(zcbor_state_t *state, const Time &input)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res = false;

    switch (input.type)
    {
    case Time::Type::Int:
        res = zcbor_int32_put(state, input.intTime);
        break;

    case Time::Type::Float:
        res = zcbor_float64_put(state, input.floatTime);
        break;

    default:
        fail("Unsupported Time type", C509_ERR_TIME_ENC_UNSUPPORTED_TYPE);
        return false;
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}

bool CBORCodec<Time>::decode_unwrapped(zcbor_state_t *state, Time &output)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res;
    int32_t int_value;
    double float_value;

    if ((res = zcbor_int32_decode(state, &int_value)))
    {
        output.type = Time::Type::Int;
        output.intTime = int_value;
    }
    else if ((res = zcbor_float64_decode(state, &float_value)))
    {
        output.type = Time::Type::Float;
        output.floatTime = float_value;
    }
    else
        fail("Invalid CBOR encoding for Time", C509_ERR_TIME_DEC_INVALID_ENCODING);

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}
