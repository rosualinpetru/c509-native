#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<CertificateSerialNumber>::encode(zcbor_state_t *state, const CertificateSerialNumber &input)
{
    if (input.bytes.len > MAX_CSN_BYTES)
        ZCBOR_ERR(C509_ERR_CSN_ENC_INVALID_LENGTH);

    if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.elements), input.bytes.len))
        ZCBOR_ERR(C509_ERR_CSN_ENC_BSTR);

    return true;
}

bool CBORCodec<CertificateSerialNumber>::decode(zcbor_state_t *state, CertificateSerialNumber &output)
{
    zcbor_string str;
    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_CSN_DEC_BSTR);

    if (str.len > MAX_CSN_BYTES)
        ZCBOR_ERR(C509_ERR_CSN_DEC_INVALID_LENGTH);

    if (!output.bytes.copy_from(str.value, str.len))
        ZCBOR_ERR(C509_ERR_CSN_DEC_BUFFER_ERROR);

    return true;
}