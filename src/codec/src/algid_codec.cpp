#include "c509_codec_internal.hpp"

using namespace C509;

bool CBORCodec<AlgorithmIdentifier>::encode(zcbor_state_t *state, const AlgorithmIdentifier &input)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res = false;

    switch (input.type)
    {
    case AlgorithmIdentifier::Type::Int:
        res = zcbor_int32_put(state, input.intAlgorithmIdentifier);
        break;

    case AlgorithmIdentifier::Type::OID:
        if (input.oidAlgorithmIdentifier.parameters.has_value)
        {
            res = zcbor_list_start_encode(state, 2) &&
                  CBORCodec<OID>::encode_unwrapped(state, input.oidAlgorithmIdentifier.algorithmIdentifier) &&
                  zcbor_bstr_encode_ptr(
                      state,
                      reinterpret_cast<const char *>(input.oidAlgorithmIdentifier.parameters.value.elements),
                      input.oidAlgorithmIdentifier.parameters.value.len) &&
                  zcbor_list_end_encode(state, 2);
        }
        else
        {
            res = CBORCodec<OID>::encode_unwrapped(state, input.oidAlgorithmIdentifier.algorithmIdentifier);
        }

        break;
    default:
        fail("Unsupported AlgorithmIdentifier type", C509_ERR_ALGID_ENC_UNSUPPORTED_TYPE);
        return false;
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}

bool CBORCodec<AlgorithmIdentifier>::decode(zcbor_state_t *state, AlgorithmIdentifier &output)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res;

    int32_t int_value;

    if ((res = zcbor_int32_decode(state, &int_value)))
    {
        output.intAlgorithmIdentifier = int_value;
        output.type = AlgorithmIdentifier::Type::Int;
    }
    else
    {
        if ((res = CBORCodec<OID>::decode_unwrapped(state, output.oidAlgorithmIdentifier.algorithmIdentifier)))
        {
            output.oidAlgorithmIdentifier.parameters.has_value = false;
            output.type = C509::AlgorithmIdentifier::Type::OID;
        }
        else
        {
            res = zcbor_list_start_decode(state) && CBORCodec<OID>::decode_unwrapped(state, output.oidAlgorithmIdentifier.algorithmIdentifier);

            zcbor_string str;

            if ((res = res && zcbor_bstr_decode(state, &str)))
            {
                if (str.len > MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES)
                    fail("AlgorithmIdentifier parameters exceeded max length", C509_ERR_ALGID_DEC_EXCEEDED_LENGTH);

                if (!output.oidAlgorithmIdentifier.parameters.value.copy_from(str.value, str.len))
                    fail("Could not copy parsed AlgorithmIdentifier parameters", C509_ERR_ALGID_DEC_BSTR_FAILED);

                res = res && zcbor_list_end_decode(state);

                output.oidAlgorithmIdentifier.parameters.has_value = true;
                output.type = C509::AlgorithmIdentifier::Type::OID;
            }
            else
                fail("Invalid CBOR encoding for AlgorithmIdentifier", C509_ERR_ALGID_DEC_INVALID_ENCODING);
        }
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}