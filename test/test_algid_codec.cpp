#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

TEST_CASE("AlgorithmIdentifier Encoding - Int Type")
{
    // Input
    C509::AlgorithmIdentifier algId;
    algId.type = C509::AlgorithmIdentifier::Type::Int;
    algId.intAlgorithmIdentifier = 15;

    // Output
    uint8_t out[MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES];
    size_t out_size;

    // Encoding
    int res = CodecTestHelper<C509::AlgorithmIdentifier, 2>::encode(out, sizeof(out), &algId, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(out_size == 1);
    REQUIRE(out[0] == 0x0F);
}

TEST_CASE("AlgorithmIdentifier Encoding - OID Type")
{
    // Input
    C509::AlgorithmIdentifier algId;
    algId.type = C509::AlgorithmIdentifier::Type::OID;
    uint32_t subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    algId.oidAlgorithmIdentifier.algorithmIdentifier.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));

    // Output
    const size_t max_size = MAX_OID_SUBIDS * sizeof(uint32_t) + sizeof(uint32_t);
    uint8_t out[max_size];
    size_t out_size;

    // Encoding
    int res = CodecTestHelper<C509::AlgorithmIdentifier, 2>::encode(out, sizeof(out), &algId, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t result[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};

    for (int i = 0; i < out_size; i++)
        REQUIRE(out[i] == result[i]);
}

TEST_CASE("AlgorithmIdentifier Encoding - OID Type with Parameters")
{
    // Input
    C509::AlgorithmIdentifier algId;
    algId.type = C509::AlgorithmIdentifier::Type::OID;
    uint32_t subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    algId.oidAlgorithmIdentifier.algorithmIdentifier.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));
    uint8_t param_data[] = {0x0a, 0x0b, 0x0c};
    algId.oidAlgorithmIdentifier.parameters.value.copy_from(param_data, sizeof(param_data));
    algId.oidAlgorithmIdentifier.parameters.has_value = true;

    // Output
    const size_t max_size = MAX_OID_SUBIDS * sizeof(uint32_t) + sizeof(uint32_t) + MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES;
    uint8_t out[max_size];
    size_t out_size;

    // Encoding
    int res = CodecTestHelper<C509::AlgorithmIdentifier, 2>::encode(out, sizeof(out), &algId, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t result[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x43, 0x0a, 0x0b, 0x0c};

    for (int i = 0; i < out_size; i++)
        REQUIRE(out[i] == result[i]);
}

TEST_CASE("AlgorithmIdentifier Decoding - Int Type")
{
    // Input: Encoded integer AlgorithmIdentifier
    uint8_t encoded_algId[] = {0x0F}; // CBOR encoded int 15
    size_t encoded_size = sizeof(encoded_algId);

    // Output: Decoded AlgorithmIdentifier structure
    C509::AlgorithmIdentifier algId;

    // Decoding
    int res = CodecTestHelper<C509::AlgorithmIdentifier, 2>::decode(encoded_algId, encoded_size, &algId, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(algId.type == C509::AlgorithmIdentifier::Type::Int);
    REQUIRE(algId.intAlgorithmIdentifier == 15);
}

TEST_CASE("AlgorithmIdentifier Decoding - OID Type")
{
    // Input: Encoded OID AlgorithmIdentifier
    uint8_t encoded_algId[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};
    size_t encoded_size = sizeof(encoded_algId);

    // Output: Decoded AlgorithmIdentifier structure
    C509::AlgorithmIdentifier algId;

    // Decoding
    int res = CodecTestHelper<C509::AlgorithmIdentifier, 2>::decode(encoded_algId, encoded_size, &algId, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(algId.type == C509::AlgorithmIdentifier::Type::OID);
    REQUIRE(algId.oidAlgorithmIdentifier.parameters.has_value == false);

    uint32_t expected_subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    REQUIRE(algId.oidAlgorithmIdentifier.algorithmIdentifier.subids.len == sizeof(expected_subids) / sizeof(uint32_t));

    for (size_t i = 0; i < algId.oidAlgorithmIdentifier.algorithmIdentifier.subids.len; i++)
        REQUIRE(algId.oidAlgorithmIdentifier.algorithmIdentifier.subids.elements[i] == expected_subids[i]);
}

TEST_CASE("AlgorithmIdentifier Decoding - OID Type with Parameters")
{
    // Input: Encoded OID AlgorithmIdentifier with parameters
    uint8_t encoded_algId[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x43, 0x0a, 0x0b, 0x0c};
    size_t encoded_size = sizeof(encoded_algId);

    // Output: Decoded AlgorithmIdentifier structure
    C509::AlgorithmIdentifier algId;

    // Decoding
    int res = CodecTestHelper<C509::AlgorithmIdentifier, 2>::decode(encoded_algId, encoded_size, &algId, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(algId.type == C509::AlgorithmIdentifier::Type::OID);
    REQUIRE(algId.oidAlgorithmIdentifier.parameters.has_value == true);
    uint8_t expected_params[] = {0x0a, 0x0b, 0x0c};
    REQUIRE(algId.oidAlgorithmIdentifier.parameters.value.len == sizeof(expected_params));

    for (size_t i = 0; i < sizeof(expected_params); i++)
        REQUIRE(algId.oidAlgorithmIdentifier.parameters.value.elements[i] == expected_params[i]);
}
