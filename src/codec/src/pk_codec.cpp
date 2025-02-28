#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<SubjectPublicKey>::encode(zcbor_state_t *state, const SubjectPublicKey &input)
{
    return true;
}

bool CBORCodec<SubjectPublicKey>::decode(zcbor_state_t *state, SubjectPublicKey &output)
{
    return true;
}
