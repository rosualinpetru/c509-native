#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<SubjectPublicKey>::encode(zcbor_state_t *state, const SubjectPublicKey &input, AlgorithmIdentifier algId)
{
    return true;
}

bool CBORCodec<SubjectPublicKey>::decode(zcbor_state_t *state, SubjectPublicKey &output, AlgorithmIdentifier algId)
{
    return true;
}
