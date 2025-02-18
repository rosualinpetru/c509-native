#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<Attribute>::encode(zcbor_state_t *state, const Attribute &input)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res = false;

    switch (input.type)
    {
    case Attribute::Type::Int:
        if ((res = zcbor_int32_put(state, input.intAttribute.attributeType)))
        {
            res = zcbor_tstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.intAttribute.attributeValue.elements),
                input.intAttribute.attributeValue.len);
        }
        break;

    case Attribute::Type::OID:
        if ((res = CBORCodec<OID>::encode(state, input.oidAttribute.attributeType)))
        {
            res = zcbor_bstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.oidAttribute.attributeValue.elements),
                input.oidAttribute.attributeValue.len);
        }
        break;
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}

bool CBORCodec<Attribute>::decode(zcbor_state_t *state, Attribute &output)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res;
    int32_t int_value;
    zcbor_string str;

    state->elem_count = 2;
    if ((res = zcbor_int32_decode(state, &int_value)))
    {
        output.type = Attribute::Type::Int;
        output.intAttribute.attributeType = int_value;

        if ((res = zcbor_tstr_decode(state, &str)))
        {
            if (str.len > MAX_ATTRIBUTE_VALUE_TSTR_BYTES)
                fail("Attribute value exceeded max length", C509_ERR_ATTR_DEC_EXCEEDED_LENGTH);

            if (!output.intAttribute.attributeValue.copy_from(str.value, str.len))
                fail("Could not copy parsed Attribute value", C509_ERR_ATTR_DEC_BSTR_FAILED);
        }
    }
    else
    {
        state->elem_count = 2;
        if ((res = CBORCodec<OID>::decode(state, output.oidAttribute.attributeType)))
        {
            output.type = Attribute::Type::OID;

            if ((res = zcbor_bstr_decode(state, &str)))
            {
                if (str.len > MAX_ATTRIBUTE_VALUE_BSTR_BYTES)
                    fail("Attribute value exceeded max length", C509_ERR_ATTR_DEC_EXCEEDED_LENGTH);

                if (!output.oidAttribute.attributeValue.copy_from(str.value, str.len))
                    fail("Could not copy parsed Attribute value", C509_ERR_ATTR_DEC_BSTR_FAILED);
            }
        }
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}