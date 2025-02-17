#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

TEST_CASE("CertificateSerialNumber Codec")
{
    // Input
    CertificateSerialNumber csn;
    csn.bytes.len = MAX_CSN_BYTES;
    for (size_t i = 0; i < MAX_CSN_BYTES; i++)
        csn.bytes.elements[i] = i;

    // Output
    uint8_t out[21];
    size_t out_size;

    // Encoding
    int res = CodecTestHelper<CertificateSerialNumber, 2>::encode(out, 21, &csn, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    REQUIRE(out_size == 21);

    for (int i = 1; i < out_size; i++)
        REQUIRE(out[i] == i - 1);
}

TEST_CASE("CertificateSerialNumber Decoding")
{
    // Input
    uint8_t in[21];
    size_t in_size = 21;

    in[0] = 0X54;

    for (size_t i = 1; i < in_size; i++)
        in[i] = i - 1;

    // Output
    CertificateSerialNumber csn;

    // Decoding
    int res = CodecTestHelper<CertificateSerialNumber, 2>::decode(in, in_size, &csn, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    for (int i = 0; i < csn.bytes.len; i++)
        REQUIRE(csn.bytes.elements[i] == i);
}

TEST_CASE("CertificateSerialNumber Decoding Failure - Exceeds Limit")
{

    // Input
    uint8_t in[22];
    size_t in_size = 22;

    in[0] = 0X55;

    for (size_t i = 1; i < in_size; i++)
        in[i] = i - 1;

    // Output
    CertificateSerialNumber csn;

    // Decoding
    int res = CodecTestHelper<CertificateSerialNumber, 2>::decode(in, in_size, &csn, NULL);

    // Assertions
    REQUIRE(res == C509_ERR_CSN_DEC_EXCEEDED_LENGTH);
}
