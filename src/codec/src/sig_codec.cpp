#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<SignatureValue>::encode(zcbor_state_t *state, const SignatureValue &input)
{
    return true;
}

bool CBORCodec<SignatureValue>::decode(zcbor_state_t *state, SignatureValue &output)
{
    return true;
}
