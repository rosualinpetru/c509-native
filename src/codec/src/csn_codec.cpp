#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<CertificateSerialNumber>::encode(zcbor_state_t *state, const CertificateSerialNumber &input)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    if (input.bytes.len > MAX_CSN_BYTES)
        fail("Certificate serial number exceeded maximum length.", C509_ERR_CSN_ENC_INVALID_INPUT);

    bool res = zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.elements), input.bytes.len);

    log_result(state, res, __PRETTY_FUNCTION__);

    return res;
}

bool CBORCodec<CertificateSerialNumber>::decode(zcbor_state_t *state, CertificateSerialNumber &output)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    zcbor_string str;

    bool res;

    state->elem_count = 1;
    if (!(res = zcbor_bstr_decode(state, &str)))
        fail("Certificate serial number byte string decoding failed.", C509_ERR_CSN_DEC_BSTR_FAILED);

    if (str.len > MAX_CSN_BYTES)
        fail("Certificate serial number exceeded maximum length.", C509_ERR_CSN_DEC_EXCEEDED_LENGTH);

    if (!output.bytes.copy_from(str.value, str.len))
        fail("Could not copy parsed CSN bytes.", C509_ERR_CSN_DEC_BUFF_COPY);

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}