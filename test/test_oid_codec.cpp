#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static auto codecHelper = CodecTestHelper(2, 1, reinterpret_cast<zcbor_decoder_t *>(CBORCodec<OID>::encode_unwrapped),
                                          reinterpret_cast<zcbor_decoder_t *>(CBORCodec<OID>::decode_unwrapped));

TEST_CASE("OID Encoding") {
    // Input
    OID oid;
    oid.subids.copy({2, 16, 840, 1, 101, 3, 4, 2, 1});

    // Output
    constexpr size_t max_size = MAX_OID_SUBIDS * sizeof(uint32_t) + sizeof(uint32_t);
    uint8_t out[max_size];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, max_size, &oid, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("OID Decoding") {
    // Input: Encoded OID data
    constexpr uint8_t encoded_oid[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};
    constexpr size_t encoded_size = sizeof(encoded_oid);

    // Output: Decoded OID structure
    OID oid;

    // Decoding
    const int res = codecHelper.decode(encoded_oid, encoded_size, &oid, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    // Expected output
    const uint32_t expected_subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    REQUIRE(oid.subids.size() == sizeof(expected_subids) / sizeof(uint32_t));

    for (size_t i = 0; i < oid.subids.size(); i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(oid.subids[i] == expected_subids[i]);
    }
}

TEST_CASE("OID Encoding - Invalid length") {
    // Input
    OID oid;
    oid.subids.copy({2});

    // Output
    constexpr size_t max_size = MAX_OID_SUBIDS * sizeof(uint32_t) + sizeof(uint32_t);
    uint8_t out[max_size];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, max_size, &oid, &out_size);

    // Assertions
    REQUIRE(res == C509_ERR_OID_ENC_INVALID_LENGTH);
}

TEST_CASE("OID Decoding - Invalid Input") {
    // Input: Empty OID data
    constexpr uint8_t encoded_oid[] = {0x40};
    constexpr size_t encoded_size = sizeof(encoded_oid);

    // Output: Decoded OID structure
    OID oid;

    // Decoding
    const int res = codecHelper.decode(encoded_oid, encoded_size, &oid, nullptr);

    // Assertions
    REQUIRE(res == C509_ERR_OID_DEC_INVALID_LENGTH);
}

TEST_CASE("OID Decoding - Malformed OID") {
    // Input: Truncated OID data
    constexpr uint8_t encoded_oid[] = {0x42, 0x60, 0x80}; // Improperly terminated base-128 sequence
    constexpr size_t encoded_size = sizeof(encoded_oid);

    // Output: Decoded OID structure
    OID oid;

    // Decoding
    const int res = codecHelper.decode(encoded_oid, encoded_size, &oid, nullptr);

    // Assertions
    REQUIRE(res == C509_ERR_OID_DEC_MALFORMED);
}
