#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static CodecTestHelper codecHelper = CodecTestHelper(2, 1, (zcbor_decoder_t *)CBORCodec<OID>::encode_unwrapped, (zcbor_decoder_t *)CBORCodec<OID>::decode_unwrapped);

TEST_CASE("OID Encoding")
{
    // Input
    OID oid;
    uint32_t subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    oid.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));

    // Output
    const size_t max_size = MAX_OID_SUBIDS * sizeof(uint32_t) + sizeof(uint32_t);
    uint8_t out[max_size];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, max_size, &oid, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("OID Decoding")
{
    // Input: Encoded OID data
    uint8_t encoded_oid[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};
    size_t encoded_size = sizeof(encoded_oid);

    // Output: Decoded OID structure
    OID oid;

    // Decoding
    int res = codecHelper.decode(encoded_oid, encoded_size, &oid, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    // Expected output
    uint32_t expected_subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    REQUIRE(oid.subids.len == sizeof(expected_subids) / sizeof(uint32_t));

    for (size_t i = 0; i < oid.subids.len; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(oid.subids.elements[i] == expected_subids[i]);
        }
}

TEST_CASE("OID Encoding - Invalid length")
{
    // Input
    OID oid;
    uint32_t subids[] = {2};
    oid.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));

    // Output
    const size_t max_size = MAX_OID_SUBIDS * sizeof(uint32_t) + sizeof(uint32_t);
    uint8_t out[max_size];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, max_size, &oid, &out_size);

    // Assertions
    REQUIRE(res == C509_ERR_OID_ENC_INVALID_LENGTH);
}

TEST_CASE("OID Decoding - Invalid Input")
{
    // Input: Empty OID data
    uint8_t encoded_oid[] = {0x40};
    size_t encoded_size = sizeof(encoded_oid);

    // Output: Decoded OID structure
    OID oid;

    // Decoding
    int res = codecHelper.decode(encoded_oid, encoded_size, &oid, NULL);

    // Assertions
    REQUIRE(res == C509_ERR_OID_DEC_INVALID_LENGTH);
}

TEST_CASE("OID Decoding - Malformed OID")
{
    // Input: Truncated OID data
    uint8_t encoded_oid[] = {0x42, 0x60, 0x80}; // Improperly terminated base-128 sequence
    size_t encoded_size = sizeof(encoded_oid);

    // Output: Decoded OID structure
    OID oid;

    // Decoding
    int res = codecHelper.decode(encoded_oid, encoded_size, &oid, NULL);

    // Assertions
    REQUIRE(res == C509_ERR_OID_DEC_MALFORMED);
}