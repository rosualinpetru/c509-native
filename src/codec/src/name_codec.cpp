#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<Name>::encode(zcbor_state_t *state, const Name &input)
{
    switch (input.type)
    {
    case Name::Type::ATTRIBUTES:
        // TODO: Optimisation for Common Name only.

        if (!zcbor_list_start_encode(state, input.attributes.len))
            ZCBOR_ERR(C509_ERR_NAME_ENC_LIST_START);

        for (size_t i = 0; i < input.attributes.len; i++)
            if (!CBORCodec<Attribute>::encode(state, input.attributes.elements[i]))
                ZCBOR_ERR(C509_ERR_NAME_ENC_ATTR);

        if (!zcbor_list_end_encode(state, input.attributes.len))
            ZCBOR_ERR(C509_ERR_NAME_ENC_LIST_END);

        return true;

    case Name::Type::TEXT:
        if (!zcbor_tstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.elements), input.bytes.len))
            ZCBOR_ERR(C509_ERR_NAME_ENC_TSTR);

        return true;

    case Name::Type::BYTES:
        if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.elements), input.bytes.len))
            ZCBOR_ERR(C509_ERR_NAME_ENC_BSTR);

        return true;
    default:
        ZCBOR_ERR(C509_ERR_NAME_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<Name>::decode(zcbor_state_t *state, Name &output)
{
    zcbor_string str;

    if (zcbor_bstr_decode(state, &str))
    {
        if (str.len > MAX_NAME_BSTR_BYTES)
            ZCBOR_ERR(C509_ERR_NAME_DEC_INVALID_LENGTH);

        if (!output.bytes.copy_from(str.value, str.len))
            ZCBOR_ERR(C509_ERR_NAME_DEC_BUFFER_ERROR);

        output.type = Name::Type::BYTES;
        return true;
    }

    if (zcbor_tstr_decode(state, &str))
    {
        if (str.len > MAX_NAME_TSTR_BYTES)
            ZCBOR_ERR(C509_ERR_NAME_DEC_INVALID_LENGTH);

        if (!output.text.copy_from(str.value, str.len))
            ZCBOR_ERR(C509_ERR_NAME_DEC_BUFFER_ERROR);

        output.type = Name::Type::TEXT;
        return true;
    }

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_NAME_DEC_LIST_START);

    bool r = zcbor_multi_decode(0, MAX_NAME_ATTRIBUTES, &output.attributes.len, (zcbor_decoder_t *)CBORCodec<Attribute>::decode, state, output.attributes.elements, sizeof(Attribute));

    if (!r)
        ZCBOR_ERR(C509_ERR_NAME_DEC_ATTR);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_NAME_DEC_LIST_END);

    output.type = Name::Type::ATTRIBUTES;
    return true;
}
