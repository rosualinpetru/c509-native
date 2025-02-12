#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<IssuerSignatureValue>::encode(zcbor_state_t *state, const IssuerSignatureValue &input)
{
    return true;
}

bool CBORCodec<IssuerSignatureValue>::decode(zcbor_state_t *state, IssuerSignatureValue &output)
{
    return true;
}
