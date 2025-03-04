#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static auto codecHelperExt = CodecTestHelper(4, 3, reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Extension>::encode),
                                             reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Extension>::decode));
static auto codecHelperExts = CodecTestHelper(4, 1, reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Extensions>::encode),
                                              reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Extensions>::decode));

TEST_CASE("Extension Encoding - OID Type") {
    // Input
    Extension ext;
    ext.type = Extension::Type::OID;
    ext.oidExtension.extensionID.subids.copy({2, 16});
    ext.oidExtension.critical = true;
    ext.oidExtension.extensionValue.copy({0x12, 0x34, 0x56});

    // Output
    uint8_t out[MAX_EXTENSION_BYTES];
    size_t out_size;

    // Encoding
    const int res = codecHelperExt.encode(out, sizeof(out), &ext, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {0x41, 0x60, 0xf5, 0x43, 0x12, 0x34, 0x56};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Extension Decoding - OID Type") {
    // Input
    constexpr uint8_t encoded_ext[] = {0x41, 0x60, 0xf4, 0x42, 0x12, 0x34};
    constexpr size_t encoded_size = sizeof(encoded_ext);

    // Ouput
    Extension ext;

    // Decoding
    const int res = codecHelperExt.decode(encoded_ext, encoded_size, &ext, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(ext.type == Extension::Type::OID);
    REQUIRE(ext.oidExtension.critical == false);
    REQUIRE(ext.oidExtension.extensionValue.size() == 2);
}

TEST_CASE("Extensions Encoding - List Type") {
    // Input
    Extensions exts{};
    exts.type = Extensions::Type::List;
    *exts.extensions.len_p() = 2;

    exts.extensions[0].type = Extension::Type::OID;
    exts.extensions[0].oidExtension.extensionID.subids.copy({1, 3, 6});
    exts.extensions[0].oidExtension.critical = false;
    exts.extensions[0].oidExtension.extensionValue.copy({0xAB, 0xCD});

    exts.extensions[1].type = Extension::Type::OID;
    exts.extensions[1].oidExtension.extensionID.subids.copy({3, 6, 9});
    exts.extensions[1].oidExtension.critical = true;
    exts.extensions[1].oidExtension.extensionValue.copy({0xDE, 0xF0});

    // Output
    uint8_t out[MAX_EXTENSION_BYTES];
    size_t out_size;

    // Encoding
    const int res = codecHelperExts.encode(out, sizeof(out), &exts, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {
        0x86, 0x42, 0x2B, 0x06, 0xf4, 0x42, 0xAB, 0xCD, 0x42, 0x7E, 0x09, 0xf5, 0x42, 0xDE, 0xF0
    };

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Extensions Decoding - List Type") {
    // Input
    constexpr uint8_t encoded_exts[] = {0x83, 0x42, 0x2B, 0x06, 0xf4, 0x42, 0xAB, 0xCD};
    constexpr size_t encoded_size = sizeof(encoded_exts);

    // Output
    Extensions exts{};

    // Decoding
    const int res = codecHelperExts.decode(encoded_exts, encoded_size, &exts, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(exts.type == Extensions::Type::List);
    REQUIRE(exts.extensions.size() == 1);
    REQUIRE(exts.extensions[0].oidExtension.critical == false);
}
