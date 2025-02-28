#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static CodecTestHelper codecHelperExt = CodecTestHelper(4, 3, (zcbor_decoder_t *)CBORCodec<Extension>::encode, (zcbor_decoder_t *)CBORCodec<Extension>::decode);
static CodecTestHelper codecHelperExts = CodecTestHelper(4, 1, (zcbor_decoder_t *)CBORCodec<Extensions>::encode, (zcbor_decoder_t *)CBORCodec<Extensions>::decode);

TEST_CASE("Extension Encoding - OID Type")
{
    // Input
    Extension ext;
    ext.type = Extension::Type::OID;
    uint32_t subids[] = {2, 16};
    ext.oidExtension.extensionID.subids.copy_from(subids, sizeof(subids) / sizeof(uint32_t));
    ext.oidExtension.critical = true;
    uint8_t ext_value[] = {0x12, 0x34, 0x56};
    ext.oidExtension.extensionValue.copy_from(ext_value, sizeof(ext_value));

    // Ouput
    uint8_t out[MAX_EXTENSION_BYTES];
    size_t out_size;

    // Encoding
    int res = codecHelperExt.encode(out, sizeof(out), &ext, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x41, 0x60, 0xf5, 0x43, 0x12, 0x34, 0x56};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Extension Decoding - OID Type")
{
    // Input
    uint8_t encoded_ext[] = {0x41, 0x60, 0xf4, 0x42, 0x12, 0x34};
    size_t encoded_size = sizeof(encoded_ext);

    // Ouput
    Extension ext;

    // Decoding
    int res = codecHelperExt.decode(encoded_ext, encoded_size, &ext, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(ext.type == Extension::Type::OID);
    REQUIRE(ext.oidExtension.critical == false);
    REQUIRE(ext.oidExtension.extensionValue.len == 2);
}

TEST_CASE("Extensions Encoding - List Type")
{
    // Input
    Extensions exts;
    exts.type = Extensions::Type::List;
    exts.extensions.len = 2;

    exts.extensions.elements[0].type = Extension::Type::OID;
    uint32_t subids1[] = {1, 3, 6};
    exts.extensions.elements[0].oidExtension.extensionID.subids.copy_from(subids1, sizeof(subids1) / sizeof(uint32_t));
    exts.extensions.elements[0].oidExtension.critical = false;
    uint8_t value1[] = {0xAB, 0xCD};
    exts.extensions.elements[0].oidExtension.extensionValue.copy_from(value1, sizeof(value1));

    exts.extensions.elements[1].type = Extension::Type::OID;
    uint32_t subids2[] = {3, 6, 9};
    exts.extensions.elements[1].oidExtension.extensionID.subids.copy_from(subids2, sizeof(subids2) / sizeof(uint32_t));
    exts.extensions.elements[1].oidExtension.critical = true;
    uint8_t value2[] = {0xDE, 0xF0};
    exts.extensions.elements[1].oidExtension.extensionValue.copy_from(value2, sizeof(value2));

    // Output
    uint8_t out[MAX_EXTENSION_BYTES];
    size_t out_size;

    // Encoding
    int res = codecHelperExts.encode(out, sizeof(out), &exts, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    uint8_t expected_result[] = {0x86, 0x42, 0x2B, 0x06, 0xf4, 0x42, 0xAB, 0xCD, 0x42, 0x7E, 0x09, 0xf5, 0x42, 0xDE, 0xF0};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
        SECTION("Checking index " + std::to_string(i))
        {
            REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
        }
}

TEST_CASE("Extensions Decoding - List Type")
{
    // Input
    uint8_t encoded_exts[] = {0x83, 0x42, 0x2B, 0x06, 0xf4, 0x42, 0xAB, 0xCD};
    size_t encoded_size = sizeof(encoded_exts);

    // Output
    Extensions exts;

    // Decoding
    int res = codecHelperExts.decode(encoded_exts, encoded_size, &exts, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(exts.type == Extensions::Type::List);
    REQUIRE(exts.extensions.len == 1);
    REQUIRE(exts.extensions.elements[0].oidExtension.critical == false);
}
