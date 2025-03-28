#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static auto codecHelper = CodecTestHelper(
    3, 1, reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Time>::encode_unwrapped),
    reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Time>::decode_unwrapped));

TEST_CASE("Time Encoding") {
    // Input
    Time time;
    time.epoch_seconds = 1623456789;

    // Output
    uint8_t out[10];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, sizeof(out), &time, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {0x1a, 0x60, 0xc3, 0xfc, 0x15};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Time Decoding") {
    // Input: Encoded integer time
    const uint8_t encoded_time[] = {0x1a, 0x60, 0xc3, 0xfc, 0x15}; // CBOR encoded int 1623456789
    constexpr size_t encoded_size = sizeof(encoded_time);

    // Output
    Time time;

    // Decoding
    const int res = codecHelper.decode(encoded_time, encoded_size, &time, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(time.epoch_seconds == 1623456789);
}

TEST_CASE("Time Decoding - Invalid Format") {
    // Input: Invalid CBOR encoding
    constexpr uint8_t encoded_time[] = {0xFF}; // Invalid CBOR value
    constexpr size_t encoded_size = sizeof(encoded_time);

    // Output
    Time time;

    // Decoding
    const int res = codecHelper.decode(encoded_time, encoded_size, &time, nullptr);

    // Assertions
    REQUIRE(res != ZCBOR_SUCCESS);
}
