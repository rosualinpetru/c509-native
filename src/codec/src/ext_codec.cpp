#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<Extension>::encode(zcbor_state_t *state, const Extension &input)
{
    switch (input.type)
    {
    case Extension::Type::OID:
        if (!CBORCodec<OID>::encode_unwrapped(state, input.oidExtension.extensionID))
            ZCBOR_ERR(C509_ERR_EXT_ENC_OID);

        if (!zcbor_bool_put(state, input.oidExtension.critical))
            ZCBOR_ERR(C509_ERR_EXT_ENC_CRITICAL);

        if (!zcbor_bstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.oidExtension.extensionValue.elements),
                input.oidExtension.extensionValue.len))
            ZCBOR_ERR(C509_ERR_EXT_ENC_BSTR_VALUE);

        return true;

    default:
        ZCBOR_ERR(C509_ERR_EXT_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<Extension>::decode(zcbor_state_t *state, Extension &output)
{
    if (!CBORCodec<OID>::decode_unwrapped(state, output.oidExtension.extensionID))
        ZCBOR_ERR(C509_ERR_EXT_DEC_OID);

    if (!zcbor_bool_decode(state, &output.oidExtension.critical))
        ZCBOR_ERR(C509_ERR_EXT_DEC_CRITICAL);

    zcbor_string str;
    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_EXT_DEC_BSTR_VALUE);

    if (str.len > MAX_EXTENSION_BYTES)
        ZCBOR_ERR(C509_ERR_EXT_DEC_INVALID_LENGTH);

    if (!output.oidExtension.extensionValue.copy_from(str.value, str.len))
        ZCBOR_ERR(C509_ERR_EXT_DEC_BUFFER_ERROR);

    output.type = Extension::Type::OID;
    return true;
}

bool CBORCodec<Extensions>::encode(zcbor_state_t *state, const Extensions &input)
{
    switch (input.type)
    {
    case Extensions::Type::MixedKeyUsage:
        if (!zcbor_int64_put(state, input.mixedKeyUsage))
            ZCBOR_ERR(C509_ERR_EXTS_ENC_MKU);

        return true;
    case Extensions::Type::List:
        if (!zcbor_list_start_encode(state, input.extensions.len))
            ZCBOR_ERR(C509_ERR_EXTS_ENC_LIST_START);

        for (size_t i = 0; i < input.extensions.len; i++)
            if (!CBORCodec<Extension>::encode(state, input.extensions.elements[i]))
                ZCBOR_ERR(C509_ERR_EXTS_ENC_EXT);

        if (!zcbor_list_end_encode(state, input.extensions.len))
            ZCBOR_ERR(C509_ERR_EXTS_ENC_LIST_END);

        return true;
    default:
        ZCBOR_ERR(C509_ERR_EXTS_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<Extensions>::decode(zcbor_state_t *state, Extensions &output)
{
    int64_t int_value;
    if (zcbor_int64_decode(state, &int_value))
    {
        output.mixedKeyUsage = int_value;
        output.type = Extensions::Type::MixedKeyUsage;
        return true;
    }

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_EXTS_DEC_LIST_START);

    bool r = zcbor_multi_decode(0, MAX_EXTENSIONS_LIST_SIZE, &output.extensions.len, (zcbor_decoder_t *)CBORCodec<Extension>::decode, state, output.extensions.elements, sizeof(Attribute));

    if (!r)
        ZCBOR_ERR(C509_ERR_EXTS_DEC_EXT);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_EXTS_DEC_LIST_END);

    output.type = Extensions::Type::List;
    return true;
}
