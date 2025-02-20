#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static CodecTestHelper codecHelper = CodecTestHelper(4, 1, (zcbor_decoder_t *)CBORCodec<Name>::encode, (zcbor_decoder_t *)CBORCodec<Name>::decode);

TEST_CASE("Name Encoding - Attributes Type")
{
    // Input
    Name name;
    name.type = Name::Type::ATTRIBUTES;

    Attribute *attr1, *attr2;

    name.attributes.len = 2;

    attr1 = &name.attributes.elements[0];
    attr2 = &name.attributes.elements[1];

    attr1->type = Attribute::Type::Int;
    attr1->intAttribute.attributeType = 42;
    uint8_t attr1_value[] = {0x12, 0x34};
    attr1->intAttribute.attributeValue.copy_from(attr1_value, sizeof(attr1_value));

    attr2->type = Attribute::Type::OID;
    uint32_t subids[] = {2, 16, 840};
    attr2->oidAttribute.attributeType.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));
    uint8_t attr2_value[] = {0x56, 0x78, 0x99};
    attr2->oidAttribute.attributeValue.copy_from(attr2_value, sizeof(attr2_value));

    // Output
    uint8_t out[MAX_NAME_BSTR_BYTES];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, sizeof(out), &name, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x84, 0x18, 0x2a, 0x62, 0x12, 0x34, 0x43, 0x60, 0x86, 0x48, 0x43, 0x56, 0x78, 0x99};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Name Encoding - Text Type")
{
    // Input
    Name name;
    name.type = Name::Type::TEXT;
    const char *text = "Test Name";
    name.text.copy_from(reinterpret_cast<const uint8_t *>(text), strlen(text));

    // Output
    uint8_t out[MAX_NAME_TSTR_BYTES];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, sizeof(out), &name, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x69, 'T', 'e', 's', 't', ' ', 'N', 'a', 'm', 'e'};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Name Encoding - Bytes Type")
{
    // Input
    Name name;
    name.type = Name::Type::BYTES;
    uint8_t bytes[] = {0xab, 0xcd, 0xef};
    name.bytes.copy_from(bytes, sizeof(bytes));

    // Output
    uint8_t out[MAX_NAME_BSTR_BYTES];
    size_t out_size;

    // Encoding
    int res = codecHelper.encode(out, sizeof(out), &name, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x43, 0xab, 0xcd, 0xef};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Name Decoding - Attributes Type")
{
    // Input
    uint8_t encoded_name[] = {0x84, 0x18, 0x2a, 0x62, 0x12, 0x34, 0x43, 0x60, 0x86, 0x48, 0x43, 0x56, 0x78, 0x99};
    size_t encoded_size = sizeof(encoded_name);

    // Output
    Name name;

    // Decoding
    int res = codecHelper.decode(encoded_name, encoded_size, &name, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(name.type == Name::Type::ATTRIBUTES);
    REQUIRE(name.attributes.len == 2);
    REQUIRE(name.attributes.elements[0].type == Attribute::Type::Int);
    REQUIRE(name.attributes.elements[1].type == Attribute::Type::OID);
}

TEST_CASE("Name Decoding - Text Type")
{
    // Input
    uint8_t encoded_name[] = {0x69, 'T', 'e', 's', 't', ' ', 'N', 'a', 'm', 'e'};
    size_t encoded_size = sizeof(encoded_name);

    // Output
    Name name;

    // Decoding
    int res = codecHelper.decode(encoded_name, encoded_size, &name, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(name.type == Name::Type::TEXT);
    REQUIRE(strncmp(reinterpret_cast<const char *>(name.text.elements), "Test Name", name.text.len) == 0);
}

TEST_CASE("Name Decoding - Bytes Type")
{
    // Input
    uint8_t encoded_name[] = {0x43, 0xAB, 0xCD, 0xEF};
    size_t encoded_size = sizeof(encoded_name);

    // Output
    Name name;

    // Decoding
    int res = codecHelper.decode(encoded_name, encoded_size, &name, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(name.type == Name::Type::BYTES);
    REQUIRE(name.bytes.len == 3);
    REQUIRE(name.bytes.elements[0] == 0xAB);
    REQUIRE(name.bytes.elements[1] == 0xCD);
    REQUIRE(name.bytes.elements[2] == 0xEF);
}
