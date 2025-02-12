#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<CertificateSerialNumber>::encode(zcbor_state_t *state, const CertificateSerialNumber &input)
{
    zcbor_log("%s\r\n", __func__);

    bool res = zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.elements), input.bytes.len);

    log_result(state, res, __func__);
    return res;
}

bool CBORCodec<CertificateSerialNumber>::decode(zcbor_state_t *state, CertificateSerialNumber &output)
{
    zcbor_log("%s\r\n", __func__);

    zcbor_string str = {
        .value = output.bytes.elements,
        .len = MAX_CSN_BYTES};

    bool res = zcbor_bstr_decode(state, &str);

    if (str.len > MAX_CSN_BYTES)
    {
        zcbor_log("Certificate serial number exceeded maximum length.");
        zcbor_error(state, 509001);
        log_result(state, false, __func__);
        return false;
    }

    log_result(state, res, __func__);
    return res;
}