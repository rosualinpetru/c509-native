#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<C509Certificate>::encode(zcbor_state_t *state, const C509Certificate &input)
{
    return zcbor_list_start_encode(state, 11) &&
           CBORCodec<TBSCertificate>::encode(state, input.tbsCertificate) &&
           CBORCodec<SignatureValue>::encode(state, input.signatureValue, input.tbsCertificate.issuerSignatureAlgorithm) &&
           zcbor_list_end_encode(state, 11);
}

bool CBORCodec<C509Certificate>::decode(zcbor_state_t *state, C509Certificate &output)
{
    return zcbor_list_start_decode(state) &&
           CBORCodec<TBSCertificate>::decode(state, output.tbsCertificate) &&
           CBORCodec<SignatureValue>::decode(state, output.signatureValue, output.tbsCertificate.issuerSignatureAlgorithm) &&
           zcbor_list_end_decode(state);
}
