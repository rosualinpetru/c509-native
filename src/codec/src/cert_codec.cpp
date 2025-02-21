#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<C509Certificate>::encode(zcbor_state_t *state, const C509Certificate &input)
{
    // TODO
    return CBORCodec<TBSCertificate>::encode(state, input.tbsCertificate) &&
           CBORCodec<IssuerSignatureValue>::encode(state, input.issuerSignatureValue);
}

bool CBORCodec<C509Certificate>::decode(zcbor_state_t *state, C509Certificate &output)
{
    // TODO
    return CBORCodec<TBSCertificate>::decode(state, output.tbsCertificate) &&
           CBORCodec<IssuerSignatureValue>::decode(state, output.issuerSignatureValue);
}
