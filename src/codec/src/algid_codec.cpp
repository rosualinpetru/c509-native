#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<AlgorithmIdentifier>::encode(zcbor_state_t *state, const AlgorithmIdentifier &input) {
    switch (input.type) {
        case AlgorithmIdentifier::Type::Int:
            if (!zcbor_int32_put(state, input.int_algorithm_identifier))
                ZCBOR_ERR(C509_ERR_ALGID_ENC_INT);

            return true;

        case AlgorithmIdentifier::Type::OID:
            if (input.oid_algorithm_identifier.parameters.has()) {
                if (!zcbor_list_start_encode(state, 2))
                    ZCBOR_ERR(C509_ERR_ALGID_ENC_LIST_START);

                if (!CBORCodec<OID>::encode_unwrapped(state, input.oid_algorithm_identifier.algorithm_identifier))
                    ZCBOR_ERR(C509_ERR_ALGID_ENC_OID);

                if (!zcbor_bstr_encode_ptr(
                    state,
                    reinterpret_cast<const char *>(input.oid_algorithm_identifier.parameters.get().data()),
                    input.oid_algorithm_identifier.parameters.get().size()))
                    ZCBOR_ERR(C509_ERR_ALGID_ENC_PARAMS);

                if (!zcbor_list_end_encode(state, 2))
                    ZCBOR_ERR(C509_ERR_ALGID_ENC_LIST_END);
            } else if (!CBORCodec<OID>::encode_unwrapped(state, input.oid_algorithm_identifier.algorithm_identifier))
                ZCBOR_ERR(C509_ERR_ALGID_ENC_OID);

            return true;

        default:
            ZCBOR_ERR(C509_ERR_ALGID_ENC_UNSUPPORTED_TYPE);
    }
}

bool CBORCodec<AlgorithmIdentifier>::decode(zcbor_state_t *state, AlgorithmIdentifier &output) {
    int32_t int_value;
    if (zcbor_int32_decode(state, &int_value)) {
        output.int_algorithm_identifier = int_value;
        output.type = AlgorithmIdentifier::Type::Int;
        return true;
    }

    if (CBORCodec<OID>::decode_unwrapped(state, output.oid_algorithm_identifier.algorithm_identifier)) {
        output.oid_algorithm_identifier.parameters.reset();
        output.type = AlgorithmIdentifier::Type::OID;
        return true;
    }

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_LIST_START);

    if (!CBORCodec<OID>::decode_unwrapped(state, output.oid_algorithm_identifier.algorithm_identifier))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_OID);

    zcbor_string str{};
    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_PARAMS);

    if (str.len > MAX_ALGORITHM_IDENTIFIER_PARAMETER_BYTES)
        ZCBOR_ERR(C509_ERR_ALGID_DEC_INVALID_LENGTH);

    if (!output.oid_algorithm_identifier.parameters.get().copy(str.value, str.len))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_BUFFER_ERROR);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(C509_ERR_ALGID_DEC_LIST_END);

    output.oid_algorithm_identifier.parameters.set_has();
    output.type = AlgorithmIdentifier::Type::OID;

    return true;
}
