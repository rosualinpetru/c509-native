#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<PublicKey>::encode(zcbor_state_t *state, const PublicKey &input) {
    if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.data()), input.bytes.size()))
        ZCBOR_ERR(C509_ERR_PK_ENC_BSTR);

    return true;
}

bool CBORCodec<PublicKey>::decode(zcbor_state_t *state, PublicKey &output) {
    zcbor_string str{};

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_PK_DEC_BSTR);

    if (str.len >= MAX_PK_BYTES)
        ZCBOR_ERR(C509_ERR_PK_DEC_INVALID_LENGTH);

    if (!output.bytes.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_PK_DEC_BUFFER_ERROR);

    return true;
}