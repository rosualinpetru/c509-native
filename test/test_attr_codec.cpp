#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

#include <iostream>
#include <iomanip>

using namespace C509;

TEST_CASE("Attribute Encoding - Int Type")
{
    // Input
    C509::Attribute attr;
    attr.type = C509::Attribute::Type::Int;
    attr.intAttribute.attributeType = 15;
    uint8_t attr_value[] = {0x12, 0x34};
    attr.intAttribute.attributeValue.copy_from(attr_value, sizeof(attr_value));

    // Output
    uint8_t out[MAX_ATTRIBUTE_VALUE_TSTR_BYTES];
    size_t out_size;

    // Encoding
    int res = CodecTestHelper<C509::Attribute, 2>::encode(out, sizeof(out), &attr, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(out_size == 4);

    uint8_t expected_out[] = {0x0F, 0x62, 0x12, 0x34};
    for (size_t i = 0; i < out_size; i++)
        REQUIRE(out[i] == expected_out[i]);
}

TEST_CASE("Attribute Encoding - OID Type")
{
    // Input
    C509::Attribute attr;
    attr.type = C509::Attribute::Type::OID;
    uint32_t subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
    attr.oidAttribute.attributeType.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));
    uint8_t attr_value[] = {0x56, 0x78, 0x99};
    attr.oidAttribute.attributeValue.copy_from(attr_value, sizeof(attr_value));

    // Output
    uint8_t out[MAX_ATTRIBUTE_VALUE_BSTR_BYTES];
    size_t out_size;

    // Encoding
    int res = CodecTestHelper<C509::Attribute, 2>::encode(out, sizeof(out), &attr, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(out_size == 14);
    uint8_t expected_out[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x63, 0x56, 0x78, 0x99};
    for (size_t i = 0; i < out_size; i++)
        REQUIRE(out[i] == expected_out[i]);
}

// TEST_CASE("Attribute Decoding - Int Type")
// {
//     // Input: Encoded integer Attribute
//     uint8_t encoded_attr[] = {0x0F, 0x42, 0x12, 0x34};
//     size_t encoded_size = sizeof(encoded_attr);

//     // Output: Decoded Attribute structure
//     C509::Attribute attr;

//     // Decoding
//     int res = CodecTestHelper<C509::Attribute, 2>::decode(encoded_attr, encoded_size, &attr, NULL);

//     // Assertions
//     REQUIRE(res == ZCBOR_SUCCESS);
//     REQUIRE(attr.type == C509::Attribute::Type::Int);
//     REQUIRE(attr.intAttribute.attributeType == 15);
//     REQUIRE(attr.intAttribute.attributeValue.len == 2);
//     REQUIRE(attr.intAttribute.attributeValue.elements[0] == 0x12);
//     REQUIRE(attr.intAttribute.attributeValue.elements[1] == 0x34);
// }

// TEST_CASE("Attribute Decoding - OID Type")
// {
//     // Input: Encoded OID Attribute
//     uint8_t encoded_attr[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x42, 0x56, 0x78};
//     size_t encoded_size = sizeof(encoded_attr);

//     // Output: Decoded Attribute structure
//     C509::Attribute attr;

//     // Decoding
//     int res = CodecTestHelper<C509::Attribute, 2>::decode(encoded_attr, encoded_size, &attr, NULL);

//     // Assertions
//     REQUIRE(res == ZCBOR_SUCCESS);
//     REQUIRE(attr.type == C509::Attribute::Type::OID);
//     uint32_t expected_subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};
//     REQUIRE(attr.oidAttribute.attributeType.subids.len == sizeof(expected_subids) / sizeof(uint32_t));
//     for (size_t i = 0; i < attr.oidAttribute.attributeType.subids.len; i++)
//         REQUIRE(attr.oidAttribute.attributeType.subids.elements[i] == expected_subids[i]);
//     REQUIRE(attr.oidAttribute.attributeValue.len == 2);
//     REQUIRE(attr.oidAttribute.attributeValue.elements[0] == 0x56);
//     REQUIRE(attr.oidAttribute.attributeValue.elements[1] == 0x78);
// }
