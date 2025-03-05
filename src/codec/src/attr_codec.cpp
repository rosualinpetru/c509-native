#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<Attribute>::encode(zcbor_state_t *state, const Attribute &input) {
    switch (input.type) {
        case Attribute::Type::Int:
            if (!zcbor_int32_put(state, input.intAttribute.attribute_type))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_INT);

            if (!zcbor_tstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.intAttribute.attribute_value.data()),
                input.intAttribute.attribute_value.size()))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_TSTR);

            return true;

        case Attribute::Type::OID:

            if (!CBORCodec<OID>::encode_unwrapped(state, input.oidAttribute.attribute_type))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_OID);

            if (!zcbor_bstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.oidAttribute.attribute_value.data()),
                input.oidAttribute.attribute_value.size()))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_BSTR);

            return true;

        default:
            ZCBOR_ERR(C509_ERR_ATTR_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<Attribute>::decode(zcbor_state_t *state, Attribute &output) {
    int32_t int_value;
    zcbor_string str{};

    if (zcbor_int32_decode(state, &int_value)) {
        output.type = Attribute::Type::Int;
        output.intAttribute.attribute_type = int_value;

        if (!zcbor_tstr_decode(state, &str))
            ZCBOR_ERR(C509_ERR_ATTR_DEC_TSTR);

        if (str.len > MAX_ATTRIBUTE_VALUE_TSTR_BYTES)
            ZCBOR_ERR(C509_ERR_ATTR_DEC_INVALID_LENGTH);

        if (!output.intAttribute.attribute_value.copy(str.value, str.len))
            ZCBOR_ERR(C509_ERR_ATTR_DEC_BUFFER_ERROR);

        return true;
    }

    if (!CBORCodec<OID>::decode_unwrapped(state, output.oidAttribute.attribute_type))
        ZCBOR_ERR(C509_ERR_ATTR_DEC_OID);

    output.type = Attribute::Type::OID;

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_ATTR_DEC_BSTR);

    if (str.len > MAX_ATTRIBUTE_VALUE_TSTR_BYTES)
        ZCBOR_ERR(C509_ERR_ATTR_DEC_INVALID_LENGTH);

    if (!output.oidAttribute.attribute_value.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_ATTR_DEC_BUFFER_ERROR);

    return true;
}
