#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static auto codecHelper = CodecTestHelper(2, 1, (zcbor_decoder_t *)CBORCodec<CertificateSerialNumber>::encode, (zcbor_decoder_t *)CBORCodec<CertificateSerialNumber>::decode);

TEST_CASE("CertificateSerialNumber Encoding")
{
    // Input
    CertificateSerialNumber csn;
    *csn.bytes.len_p() = MAX_CSN_BYTES;
    for (size_t i = 0; i < MAX_CSN_BYTES; i++)
        csn.bytes[i] = i;

    // Output
    uint8_t out[21];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, 21, &csn, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    REQUIRE(out_size == 21);

    for (int i = 1; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(i - 1));
        }
}

TEST_CASE("CertificateSerialNumber Decoding")
{
    // Input
    uint8_t in[21];
    constexpr size_t in_size = 21;

    in[0] = 0X54;

    for (size_t i = 1; i < in_size; i++)
        in[i] = i - 1;

    // Output
    CertificateSerialNumber csn;

    // Decoding
    const int res = codecHelper.decode(in, in_size, &csn, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    for (int i = 0; i < csn.bytes.size(); i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(csn.bytes[i] == i);
        }
}

TEST_CASE("CertificateSerialNumber Decoding Failure - Exceeds Limit")
{

    // Input
    uint8_t in[22];
    constexpr size_t in_size = 22;

    in[0] = 0X55;

    for (size_t i = 1; i < in_size; i++)
        in[i] = i - 1;

    // Output
    CertificateSerialNumber csn;

    // Decoding
    const int res = codecHelper.decode(in, in_size, &csn, nullptr);

    // Assertions
    REQUIRE(res == C509_ERR_CSN_DEC_INVALID_LENGTH);
}
