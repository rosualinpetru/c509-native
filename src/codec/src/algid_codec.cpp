#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<AlgorithmIdentifier>::encode(zcbor_state_t *state, const AlgorithmIdentifier &input)
{
    switch (input.type)
    {
    case AlgorithmIdentifier::Type::Int:
        if (!zcbor_int32_put(state, input.intAlgorithmIdentifier))
            ZCBOR_ERR(C509_ERR_ALGID_ENC_INT);

        return true;

    case AlgorithmIdentifier::Type::OID:
        if (input.oidAlgorithmIdentifier.parameters.has_value)
        {
            if (!zcbor_list_start_encode(state, 2))
                ZCBOR_ERR(C509_ERR_ALGID_ENC_LIST_START);

            if (!CBORCodec<OID>::encode_unwrapped(state, input.oidAlgorithmIdentifier.algorithmIdentifier))
                ZCBOR_ERR(C509_ERR_ALGID_ENC_OID);

            if (!zcbor_bstr_encode_ptr(
                    state,
                    reinterpret_cast<const char *>(input.oidAlgorithmIdentifier.parameters.value.elements),
                    input.oidAlgorithmIdentifier.parameters.value.len))
                ZCBOR_ERR(C509_ERR_ALGID_ENC_PARAMS);

            if (!zcbor_list_end_encode(state, 2))
                ZCBOR_ERR(C509_ERR_ALGID_ENC_LIST_END);
        }
        else if (!CBORCodec<OID>::encode_unwrapped(state, input.oidAlgorithmIdentifier.algorithmIdentifier))
            ZCBOR_ERR(C509_ERR_ALGID_ENC_OID);

        return true;

    default:
        ZCBOR_ERR(C509_ERR_ALGID_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<AlgorithmIdentifier>::decode(zcbor_state_t *state, AlgorithmIdentifier &output)
{

    int32_t int_value;
    if (zcbor_int32_decode(state, &int_value))
    {
        output.intAlgorithmIdentifier = int_value;
        output.type = AlgorithmIdentifier::Type::Int;
        return true;
    }

    if (CBORCodec<OID>::decode_unwrapped(state, output.oidAlgorithmIdentifier.algorithmIdentifier))
    {
        output.oidAlgorithmIdentifier.parameters.has_value = false;
        output.type = C509::AlgorithmIdentifier::Type::OID;
        return true;
    }

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_LIST_START);

    if (!CBORCodec<OID>::decode_unwrapped(state, output.oidAlgorithmIdentifier.algorithmIdentifier))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_OID);

    zcbor_string str;
    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_PARAMS);

    if (str.len > MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES)
        ZCBOR_ERR(C509_ERR_ALGID_DEC_INVALID_LENGTH);

    if (!output.oidAlgorithmIdentifier.parameters.value.copy_from(str.value, str.len))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_BUFFER_ERROR);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_LIST_END);

    output.oidAlgorithmIdentifier.parameters.has_value = true;
    output.type = C509::AlgorithmIdentifier::Type::OID;

    return true;
}