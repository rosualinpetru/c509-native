#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<COSE_C509>::encode(zcbor_state_t *state, const COSE_C509 &input) {
    if (input.certificates.empty())
        ZCBOR_ERR(C509_ERR_COSE_ENC_EMPTY);

    if (input.certificates.size() > 1)
        if (!zcbor_list_start_encode(state, input.certificates.size()))
            ZCBOR_ERR(C509_ERR_COSE_ENC_LIST_START);

    for (size_t i = 0; i < input.certificates.size(); i++)
        if (!CBORCodec<C509Certificate>::encode(state, input.certificates[i]))
            ZCBOR_ERR(C509_ERR_COSE_ENC_C509);

    if (input.certificates.size() > 1)
        if (!zcbor_list_end_encode(state, input.certificates.size()))
            ZCBOR_ERR(C509_ERR_COSE_ENC_LIST_END);

    return true;
}

bool CBORCodec<COSE_C509>::decode(zcbor_state_t *state, COSE_C509 &output) {
    if (CBORCodec<C509Certificate>::decode(state, output.certificates[0])) {
        *output.certificates.len_p() = 1;
        return true;
    }

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_COSE_DEC_LIST_START);

    const bool r = zcbor_multi_decode(0, MAX_C509_BAG, output.certificates.len_p(),
                                      reinterpret_cast<zcbor_decoder_t *>(CBORCodec<C509Certificate>::decode), state,
                                      output.certificates.data_p(),
                                      sizeof(C509Certificate));

    if (!r)
        ZCBOR_ERR(C509_ERR_COSE_DEC_C509);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_COSE_DEC_LIST_END);


    return true;
}
