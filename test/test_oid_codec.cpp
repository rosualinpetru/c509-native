#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <iomanip>

#include "test_helper.cpp"

using namespace C509;

TEST_CASE("OID Codec")
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
    int res = CodecTestHelper<OID, 2>::encode(out, max_size, &oid, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t result[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};

    for (int i = 0; i < out_size; i++)
        REQUIRE(out[i] == result[i]);
}

// TEST_CASE("OID Decoding")
// {
//     // Input
//     uint8_t in[21];
//     size_t in_size = 21;

//     in[0] = 0X54;

//     for (size_t i = 1; i < in_size; i++)
//         in[i] = i - 1;

//     // Output
//     CertificateSerialNumber csn;

//     // Decoding
//     int res = CodecTestHelper<CertificateSerialNumber, 2>::decode(in, in_size, &csn, NULL);

//     // Assertions
//     REQUIRE(res == ZCBOR_SUCCESS);

//     for (int i = 0; i < csn.bytes.len; i++)
//         REQUIRE(csn.bytes.elements[i] == i);
// }

// TEST_CASE("CertificateSerialNumber Decoding Failure - Exceeds Limit")
// {

//     // Input
//     uint8_t in[22];
//     size_t in_size = 22;

//     in[0] = 0X55;

//     for (size_t i = 1; i < in_size; i++)
//         in[i] = i - 1;

//     // Output
//     CertificateSerialNumber csn;

//     // Decoding
//     int res = CodecTestHelper<CertificateSerialNumber, 2>::decode(in, in_size, &csn, NULL);

//     // Assertions
//     REQUIRE(res == 509001);
// }
