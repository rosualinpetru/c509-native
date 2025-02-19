#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static CodecTestHelper codecHelper = CodecTestHelper(2, (zcbor_decoder_t *)CBORCodec<Attribute>::encode, (zcbor_decoder_t *)CBORCodec<Attribute>::decode);

TEST_CASE("Attribute Encoding - Int Type")
{
    // Input
    C509::Attribute attr;
    attr.type = C509::Attribute::Type::Int;
    attr.intAttribute.attributeType = 15;
    uint8_t attr_value[] = {0x12, 0x34, 0x56};
    attr.intAttribute.attributeValue.copy_from(attr_value, sizeof(attr_value));

    // Output
    uint8_t out[MAX_ATTRIBUTE_VALUE_TSTR_BYTES];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, sizeof(out), &attr, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x0f, 0x63, 0x12, 0x34, 0x56};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
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
    int res = codecHelper.encode(out, sizeof(out), &attr, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x43, 0x56, 0x78, 0x99};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Attribute Decoding - Int Type")
{
    // Input: Encoded integer Attribute
    uint8_t encoded_attr[] = {0x0F, 0x62, 0x12, 0x34};
    size_t encoded_size = sizeof(encoded_attr);

    // Output: Decoded Attribute structure
    C509::Attribute attr;

    // Decoding
    int res = codecHelper.decode(encoded_attr, encoded_size, &attr, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(attr.type == C509::Attribute::Type::Int);
    REQUIRE(attr.intAttribute.attributeType == 15);
    REQUIRE(attr.intAttribute.attributeValue.len == 2);
    REQUIRE(HexByte(attr.intAttribute.attributeValue.elements[0]) == HexByte(0x12));
    REQUIRE(HexByte(attr.intAttribute.attributeValue.elements[1]) == HexByte(0x34));
}

TEST_CASE("Attribute Decoding - OID Type")
{
    // Input: Encoded OID Attribute
    uint8_t encoded_attr[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x42, 0x56, 0x78};
    size_t encoded_size = sizeof(encoded_attr);

    // Output: Decoded Attribute structure
    C509::Attribute attr;

    // Decoding
    int res = codecHelper.decode(encoded_attr, encoded_size, &attr, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(attr.type == C509::Attribute::Type::OID);

    uint32_t expected_subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};

    REQUIRE(attr.oidAttribute.attributeType.subids.len == sizeof(expected_subids) / sizeof(uint32_t));

    for (size_t i = 0; i < attr.oidAttribute.attributeType.subids.len; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(attr.oidAttribute.attributeType.subids.elements[i] == expected_subids[i]);
        }

    REQUIRE(attr.oidAttribute.attributeValue.len == 2);
    REQUIRE(HexByte(attr.oidAttribute.attributeValue.elements[0]) == HexByte(0x56));
    REQUIRE(HexByte(attr.oidAttribute.attributeValue.elements[1]) == HexByte(0x78));
}
