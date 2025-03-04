#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<SignatureValue>::encode(zcbor_state_t *state, const SignatureValue &input) {
    if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.data()), input.bytes.size()))
        ZCBOR_ERR(C509_ERR_SIG_ENC_BSTR);

    return true;
}

bool CBORCodec<SignatureValue>::decode(zcbor_state_t *state, SignatureValue &output) {
    zcbor_string str{};

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_SIG_DEC_BSTR);

    if (str.len >= MAX_SIG_BYTES)
        ZCBOR_ERR(C509_ERR_SIG_DEC_INVALID_LENGTH);

    if (!output.bytes.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_SIG_DEC_BUFFER_ERROR);

    return true;
}
