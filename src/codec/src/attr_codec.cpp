#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<Attribute>::encode(zcbor_state_t *state, const Attribute &input) {
    switch (input.type) {
        case Attribute::Type::Int:
            if (!zcbor_int32_put(state, input.attribute_type.integer))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_INT);

            if (!zcbor_tstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.attribute_value.data()),
                input.attribute_value.size()))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_TSTR);

            return true;

        case Attribute::Type::OID:

            if (!CBORCodec<OID>::encode_unwrapped(state, input.attribute_type.oid))
                ZCBOR_ERR(C509_ERR_ATTR_ENC_OID);

            if (!zcbor_bstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.attribute_value.data()),
                input.attribute_value.size()))
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
        output.attribute_type.integer = int_value;

        if (!zcbor_tstr_decode(state, &str))
            ZCBOR_ERR(C509_ERR_ATTR_DEC_TSTR);

        if (str.len > MAX_ATTRIBUTE_VALUE_BYTES)
            ZCBOR_ERR(C509_ERR_ATTR_DEC_INVALID_LENGTH);

        if (!output.attribute_value.copy(str.value, str.len))
            ZCBOR_ERR(C509_ERR_ATTR_DEC_BUFFER_ERROR);

        return true;
    }

    if (!CBORCodec<OID>::decode_unwrapped(state, output.attribute_type.oid))
        ZCBOR_ERR(C509_ERR_ATTR_DEC_OID);

    output.type = Attribute::Type::OID;

    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_ATTR_DEC_BSTR);

    if (str.len > MAX_ATTRIBUTE_VALUE_BYTES)
        ZCBOR_ERR(C509_ERR_ATTR_DEC_INVALID_LENGTH);

    if (!output.attribute_value.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_ATTR_DEC_BUFFER_ERROR);

    return true;
}
