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
        res = CBORCodec<OID>::encode(state, input.oidAlgorithmIdentifier.algorithmIdentifier);

        if (res && input.oidAlgorithmIdentifier.parameters.has_value)
        {
            res = zcbor_bstr_encode_ptr(
                state,
                reinterpret_cast<const char *>(input.oidAlgorithmIdentifier.parameters.value.elements),
                input.oidAlgorithmIdentifier.parameters.value.len);
        }

        break;
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}

bool CBORCodec<AlgorithmIdentifier>::decode(zcbor_state_t *state, AlgorithmIdentifier &output)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    bool res = false;

    int32_t int_value;
    zcbor_string str;

    if (zcbor_int32_decode(state, &int_value))
    {
        output.type = AlgorithmIdentifier::Type::Int;
        output.intAlgorithmIdentifier = int_value;
        res = true;
    }
    else if (CBORCodec<OID>::decode(state, output.oidAlgorithmIdentifier.algorithmIdentifier))
    {
        if (zcbor_bstr_decode(state, &str))
        {
            if (str.len > MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES)
                fail("AlgorithmIdentifier parameters exceeded max length", 509005);

            if (!output.oidAlgorithmIdentifier.parameters.value.copy_from(str.value, str.len))
                fail("Could not copy parsed AlgorithmIdentifier parameters", 509006);

            output.oidAlgorithmIdentifier.parameters.has_value = true;
        } else {
            output.oidAlgorithmIdentifier.parameters.has_value = ;
        }

        res = true;
    }
    else
    {
        fail("Invalid AlgorithmIdentifier encoding", 509007);
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}
