#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<TBSCertificate>::encode(zcbor_state_t *state, const TBSCertificate &input)
{
    zcbor_log("%s\r\n", __func__);

    bool res = zcbor_uint32_put(state, input.c509CertificateType) &&
               CBORCodec<CertificateSerialNumber>::encode(state, input.certificateSerialNumber);

    log_result(state, res, __func__);

    return res;
}

bool CBORCodec<TBSCertificate>::decode(zcbor_state_t *state, TBSCertificate &output)
{
    zcbor_log("%s\r\n", __func__);

    unsigned int temp;

    bool res = zcbor_uint32_decode(state, &temp) &&
               CBORCodec<CertificateSerialNumber>::decode(state, output.certificateSerialNumber);

    if(temp != 2 && temp != 3) {
        zcbor_log("Certificate type is invalid. Should be 2 or 3 but was: %d", temp);
        zcbor_error(state, 509000);
        log_result(state, false, __func__);
        return false;
    }

    output.c509CertificateType = temp;

    log_result(state, res, __func__);

    return res;
}
