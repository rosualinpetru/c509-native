#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<C509PrivateKey>::encode(zcbor_state_t *state, const C509PrivateKey &input) {
    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.subjectPrivateKeyAlgorithm))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_ATTR);

    if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.subjectPrivateKey.data()),
                               input.subjectPrivateKey.size()))
        ZCBOR_ERR(C509_ERR_PRIV_ENC_BSTR);


    return true;
}

bool CBORCodec<C509PrivateKey>::decode(zcbor_state_t *state, C509PrivateKey &output) {
    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.subjectPrivateKeyAlgorithm))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_ATTR);

    zcbor_string str{};

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_BSTR);

    if (str.len >= MAX_SIG_BYTES)
        ZCBOR_ERR(C509_ERR_PRIV_DEC_INVALID_LENGTH);

    if (!output.subjectPrivateKey.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_PRIV_DEC_BUFFER_ERROR);

    return true;
}
