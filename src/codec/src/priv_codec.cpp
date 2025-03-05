#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<C509PrivateKey>::encode(zcbor_state_t *state, const C509PrivateKey &input) {
    if (!zcbor_list_start_encode(state, 2))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_LIST_START);

    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.subject_private_key_algorithm))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_ATTR);

    if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.subject_private_key.data()),
                               input.subject_private_key.size()))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_BSTR);

    if (!zcbor_list_end_encode(state, 2))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_LIST_END);

    return true;
}

bool CBORCodec<C509PrivateKey>::decode(zcbor_state_t *state, C509PrivateKey &output) {
    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_LIST_START);

    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.subject_private_key_algorithm))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_ATTR);

    zcbor_string str{};

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_BSTR);

    if (str.len >= MAX_SIG_BYTES)
        ZCBOR_ERR(C509_ERR_PRIV_DEC_INVALID_LENGTH);

    if (!output.subject_private_key.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_BUFFER_ERROR);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_LIST_END);

    return true;
}
