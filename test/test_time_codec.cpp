#include <catch2/catch_test_macros.hpp>


#include <iostream>
#include <iomanip>

#include "test_helper.cpp"

using namespace C509;

static CodecTestHelper codecHelper = CodecTestHelper(3, (zcbor_decoder_t *)CBORCodec<Time>::encode_unwrapped, (zcbor_decoder_t *)CBORCodec<Time>::decode_unwrapped);

TEST_CASE("Time Encoding - Int Type")
{
    // Input
    Time time;
    time.type = Time::Type::Int;
    time.intTime = 1623456789;

    // Output
    uint8_t out[10];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, sizeof(out), &time, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x1a, 0x60, 0xc3, 0xfc, 0x15};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Time Encoding - Float Type")
{
    // Input
    Time time;
    time.type = Time::Type::Float;
    time.floatTime = 1623456789.123;

    // Output
    uint8_t out[10];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, sizeof(out), &time, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0xfb, 0x41, 0xd8, 0x30, 0xff, 0x05, 0x47, 0xdf, 0x3b};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Time Decoding - Int Type")
{
    // Input: Encoded integer time
    uint8_t encoded_time[] = {0x1a, 0x60, 0xc3, 0xfc, 0x15}; // CBOR encoded int 1623456789
    size_t encoded_size = sizeof(encoded_time);

    // Output
    Time time;

    // Decoding
    int res = codecHelper.decode(encoded_time, encoded_size, &time, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(time.type == Time::Type::Int);
    REQUIRE(time.intTime == 1623456789);
}

TEST_CASE("Time Decoding - Float Type")
{
    // Input: Encoded float time
    uint8_t encoded_time[] = {0xfb, 0x41, 0xd8, 0x30, 0xff, 0x05, 0x47, 0xdf, 0x3b}; // CBOR encoded float 1623456789.123
    size_t encoded_size = sizeof(encoded_time);

    // Output
    Time time;

    // Decoding
    int res = codecHelper.decode(encoded_time, encoded_size, &time, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(time.type == Time::Type::Float);
    REQUIRE(time.floatTime == 1623456789.123);
}

TEST_CASE("Time Decoding - Invalid Format")
{
    // Input: Invalid CBOR encoding
    uint8_t encoded_time[] = {0xFF}; // Invalid CBOR value
    size_t encoded_size = sizeof(encoded_time);

    // Output
    Time time;

    // Decoding
    int res = codecHelper.decode(encoded_time, encoded_size, &time, NULL);

    // Assertions
    REQUIRE(res == C509_ERR_TIME_DEC_INVALID_ENCODING);
}

TEST_CASE("Time Decoding - Unsupported Type")
{
    // Input: Unsupported CBOR type (e.g., text string)
    uint8_t encoded_time[] = {0x64, 0x74, 0x69, 0x6D, 0x65}; // "time" as CBOR string
    size_t encoded_size = sizeof(encoded_time);

    // Output
    Time time;

    // Decoding
    int res = codecHelper.decode(encoded_time, encoded_size, &time, NULL);

    // Assertions
    REQUIRE(res == C509_ERR_TIME_DEC_INVALID_ENCODING);
}
