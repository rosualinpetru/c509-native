#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<Certificate>::encode(zcbor_state_t *state, const Certificate &input)
{
    zcbor_log("%s\r\n", __func__);

    bool res = CBORCodec<TBSCertificate>::encode(state, input.tbsCertificate) &&
               CBORCodec<IssuerSignatureValue>::encode(state, input.issuerSignatureValue);

    log_result(state, res, __func__);

    return res;
}

bool CBORCodec<Certificate>::decode(zcbor_state_t *state, Certificate &output)
{
    zcbor_log("%s\r\n", __func__);

    bool res = CBORCodec<TBSCertificate>::decode(state, output.tbsCertificate) &&
               CBORCodec<IssuerSignatureValue>::decode(state, output.issuerSignatureValue);

    log_result(state, res, __func__);

    return res;
}
