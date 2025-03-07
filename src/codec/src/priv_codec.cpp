#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<PrivateKey>::encode(zcbor_state_t *state, const PrivateKey &input) {
    if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.data()), input.bytes.size()))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_BSTR);

    return true;
}

bool CBORCodec<PrivateKey>::decode(zcbor_state_t *state, PrivateKey &output) {
    zcbor_string str{};

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_BSTR);

    if (str.len >= MAX_PRIV_KEY_BYTES)
        ZCBOR_ERR(C509_ERR_PRIV_DEC_INVALID_LENGTH);

    if (!output.bytes.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_BUFFER_ERROR);

    return true;
}


bool CBORCodec<PrivateKeyInfo>::encode(zcbor_state_t *state, const PrivateKeyInfo &input) {
    if (!zcbor_list_start_encode(state, 2))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_ENC_LIST_START);

    if (!CBORCodec<PrivateKey>::encode(state, input.private_key))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_ENC_PRIV);

    if (!CBORCodec<PublicKey>::encode(state, input.public_key))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_ENC_PK);

    if (!zcbor_list_end_encode(state, 2))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_ENC_LIST_END);

    return true;
}

bool CBORCodec<PrivateKeyInfo>::decode(zcbor_state_t *state, PrivateKeyInfo &output) {
    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_DEC_LIST_START);

    if (!CBORCodec<PrivateKey>::decode(state, output.private_key))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_DEC_PRIV);

    if (!CBORCodec<PublicKey>::decode(state, output.public_key))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_DEC_PK);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_PRIV_INFO_DEC_LIST_END);

    return true;
}

bool CBORCodec<C509PrivateKey>::encode(zcbor_state_t *state, const C509PrivateKey &input) {
    if (!zcbor_list_start_encode(state, 2))
        ZCBOR_ERR(C509_ERR_PRIVK_ENC_LIST_START);

    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.subject_private_key_algorithm))
        ZCBOR_ERR(C509_ERR_PRIVK_ENC_ALG_ID);

    if (!CBORCodec<PrivateKeyInfo>::encode(state, input.subject_private_key_info))
        ZCBOR_ERR(C509_ERR_PRIVK_ENC_INFO);

    if (!zcbor_list_end_encode(state, 2))
        ZCBOR_ERR(C509_ERR_PRIVK_ENC_LIST_END);

    return true;
}

bool CBORCodec<C509PrivateKey>::decode(zcbor_state_t *state, C509PrivateKey &output) {
    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_PRIVK_DEC_LIST_START);

    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.subject_private_key_algorithm))
        ZCBOR_ERR(C509_ERR_PRIVK_DEC_ALG_ID);

    if (!CBORCodec<PrivateKeyInfo>::decode(state, output.subject_private_key_info))
        ZCBOR_ERR(C509_ERR_PRIVK_DEC_INFO);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_PRIVK_DEC_LIST_END);

    return true;
}

bool CBORCodec<C509PEM>::encode(zcbor_state_t *state, const C509PEM &input) {
    if (!zcbor_list_start_encode(state, 2))
        ZCBOR_ERR(C509_ERR_C509PEM_ENC_LIST_START);

    if (!CBORCodec<C509PrivateKey>::encode(state, input.private_key))
        ZCBOR_ERR(C509_ERR_C509PEM_ENC_PRIVK);

    if (input.cose_c509.has()) {
        if (!CBORCodec<COSE_C509>::encode(state, input.cose_c509.get()))
            ZCBOR_ERR(C509_ERR_C509PEM_ENC_COSEC509);
    } else {
        if (zcbor_nil_put(state, nullptr))
            ZCBOR_ERR(C509_ERR_C509PEM_ENC_NIL);
    }

    if (!zcbor_list_end_encode(state, 2))
        ZCBOR_ERR(C509_ERR_C509PEM_ENC_LIST_END);

    return true;
}

bool CBORCodec<C509PEM>::decode(zcbor_state_t *state, C509PEM &output) {
    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_C509PEM_DEC_LIST_START);

    if (!CBORCodec<C509PrivateKey>::encode(state, output.private_key))
        ZCBOR_ERR(C509_ERR_C509PEM_ENC_PRIVK);


    if (!zcbor_nil_expect(state, nullptr)) {
        if (!CBORCodec<COSE_C509>::encode(state, output.cose_c509.get()))
            ZCBOR_ERR(C509_ERR_C509PEM_DEC_COSEC509);
    } else
        output.cose_c509.reset();

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_C509PEM_DEC_LIST_END);

    return true;
}