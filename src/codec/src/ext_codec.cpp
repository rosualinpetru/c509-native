#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<Extension>::encode(zcbor_state_t *state, const Extension &input) {
    switch (input.type) {
        case Extension::Type::OID:
            if (!CBORCodec<OID>::encode_unwrapped(state, input.oid_extension.extension_id))
                ZCBOR_ERR(C509_ERR_EXT_ENC_OID);

            if (!zcbor_bool_put(state, input.oid_extension.critical))
                ZCBOR_ERR(C509_ERR_EXT_ENC_CRITICAL);

            if (!zcbor_bstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.oid_extension.extension_value.data()),
                input.oid_extension.extension_value.size()))
                ZCBOR_ERR(C509_ERR_EXT_ENC_BSTR_VALUE);

            return true;

        case Extension::Type::Int:
            if (!zcbor_int32_put(state, input.int_extension.extension_id))
                ZCBOR_ERR(C509_ERR_EXT_ENC_INT);

            switch (abs(input.int_extension.extension_id)) {
                case 1: {
                    const auto *sku = static_cast<SubjectKeyIdentifier *>(input.int_extension.extension);
                    if (!zcbor_bstr_encode_ptr(
                        state,
                        reinterpret_cast<const char *>(sku->value.data()),
                        sku->value.size()))
                        ZCBOR_ERR(C509_ERR_EXT_ENC_VALUE);
                    break;
                }
                case 4: {
                    const auto *bc = static_cast<BasicConstraints *>(input.int_extension.extension);
                    if (!zcbor_int32_put(state, bc->value))
                        ZCBOR_ERR(C509_ERR_EXT_ENC_VALUE);
                    break;
                }
                case 2: {
                    const auto ku = static_cast<KeyUsage *>(input.int_extension.extension);
                    if (!zcbor_int32_put(state, ku->value))
                        ZCBOR_ERR(C509_ERR_EXT_ENC_VALUE);
                    break;
                }
                default:
                    ZCBOR_ERR(C509_ERR_EXT_ENC_UNSUPPORTED_TYPE);
            }

            return true;

        default:
            ZCBOR_ERR(C509_ERR_EXT_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<Extension>::decode(zcbor_state_t *state, Extension &output) {
    int32_t int_value;
    if (zcbor_int32_decode(state, &int_value)) {
        output.type = Extension::Type::Int;
        output.int_extension.extension_id = int_value;

        switch (abs(output.int_extension.extension_id)) {
            case 1: {
                auto *sku = new SubjectKeyIdentifier(); // TODO: I am sorry for this, but I am in a hurry - memory leak
                zcbor_string str{};
                if (!zcbor_bstr_decode(state, &str))
                    ZCBOR_ERR(C509_ERR_EXT_DEC_BSTR_VALUE);

                if (str.len > sku->value.capacity())
                    ZCBOR_ERR(C509_ERR_EXT_DEC_INVALID_LENGTH);

                if (!sku->value.copy(str.value, str.len))
                    ZCBOR_ERR(C509_ERR_EXT_DEC_BUFFER_ERROR);

                output.int_extension.extension = sku;
                break;
            }
            case 4: {
                auto *bc = new BasicConstraints();
                if (!zcbor_int32_decode(state, &int_value))
                    ZCBOR_ERR(C509_ERR_EXT_DEC_VALUE);
                bc->value = int_value;
                output.int_extension.extension = bc;
                break;
            }
            case 2: {
                auto *ku = new KeyUsage({});
                if (!zcbor_int32_decode(state, &int_value))
                    ZCBOR_ERR(C509_ERR_EXT_DEC_VALUE);
                ku->value = int_value;
                output.int_extension.extension = ku;
                break;
            }
            default:
                ZCBOR_ERR(C509_ERR_EXT_ENC_UNSUPPORTED_TYPE);
        }


        return true;
    }


    if (!CBORCodec<OID>::decode_unwrapped(state, output.oid_extension.extension_id))
        ZCBOR_ERR(C509_ERR_EXT_DEC_OID);

    if (!zcbor_bool_decode(state, &output.oid_extension.critical))
        ZCBOR_ERR(C509_ERR_EXT_DEC_CRITICAL);

    zcbor_string str{};
    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_EXT_DEC_BSTR_VALUE);

    if (str.len > MAX_EXTENSION_BYTES)
        ZCBOR_ERR(C509_ERR_EXT_DEC_INVALID_LENGTH);

    if (!output.oid_extension.extension_value.copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_EXT_DEC_BUFFER_ERROR);

    output.type = Extension::Type::OID;
    return true;
}

bool CBORCodec<Extensions>::encode(zcbor_state_t *state, const Extensions &input) {
    switch (input.type) {
        case Extensions::Type::MixedKeyUsage:
            if (!zcbor_int64_put(state, input.mixed_key_usage))
                ZCBOR_ERR(C509_ERR_EXTS_ENC_MKU);

            return true;
        case Extensions::Type::List:
            if (!zcbor_list_start_encode(state, input.extensions.size()))
                ZCBOR_ERR(C509_ERR_EXTS_ENC_LIST_START);

            for (size_t i = 0; i < input.extensions.size(); i++)
                if (!CBORCodec<Extension>::encode(state, input.extensions[i]))
                    ZCBOR_ERR(C509_ERR_EXTS_ENC_EXT);

            if (!zcbor_list_end_encode(state, input.extensions.size()))
                ZCBOR_ERR(C509_ERR_EXTS_ENC_LIST_END);

            return true;
        default:
            ZCBOR_ERR(C509_ERR_EXTS_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<Extensions>::decode(zcbor_state_t *state, Extensions &output) {
    int64_t int_value;
    if (zcbor_int64_decode(state, &int_value)) {
        output.mixed_key_usage = int_value;
        output.type = Extensions::Type::MixedKeyUsage;
        return true;
    }

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_EXTS_DEC_LIST_START);

    bool r = zcbor_multi_decode(0, MAX_EXTENSIONS_LIST_SIZE, output.extensions.len_p(),
                                reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Extension>::decode), state,
                                output.extensions.data_p(),
                                sizeof(Attribute));

    if (!r)
        ZCBOR_ERR(C509_ERR_EXTS_DEC_EXT);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_EXTS_DEC_LIST_END);

    output.type = Extensions::Type::List;
    return true;
}
