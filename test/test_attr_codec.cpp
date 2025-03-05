#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static auto codecHelper = CodecTestHelper(2, 2, reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Attribute>::encode),
                                          reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Attribute>::decode));

TEST_CASE("Attribute Encoding - Int Type") {
    // Input
    Attribute attr{};
    attr.type = Attribute::Type::Int;
    attr.intAttribute.attribute_type = 15;
    attr.intAttribute.attribute_value.copy({0x12, 0x34, 0x56});

    // Output
    uint8_t out[MAX_ATTRIBUTE_VALUE_TSTR_BYTES];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, sizeof(out), &attr, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {0x0f, 0x63, 0x12, 0x34, 0x56};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Attribute Encoding - OID Type") {
    // Input
    Attribute attr{};
    attr.type = Attribute::Type::OID;
    attr.oidAttribute.attribute_type.subids.copy({2, 16, 840, 1, 101, 3, 4, 2, 1});
    attr.oidAttribute.attribute_value.copy({0x56, 0x78, 0x99});

    // Output
    uint8_t out[MAX_ATTRIBUTE_VALUE_BSTR_BYTES];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, sizeof(out), &attr, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {
        0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x43, 0x56, 0x78, 0x99
    };

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Attribute Decoding - Int Type") {
    // Input
    constexpr uint8_t encoded_attr[] = {0x0F, 0x62, 0x12, 0x34};
    constexpr size_t encoded_size = sizeof(encoded_attr);

    // Output
    Attribute attr{};

    // Decoding
    int res = codecHelper.decode(encoded_attr, encoded_size, &attr, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(attr.type == Attribute::Type::Int);
    REQUIRE(attr.intAttribute.attribute_type == 15);
    REQUIRE(attr.intAttribute.attribute_value.size() == 2);
    REQUIRE(HexByte(attr.intAttribute.attribute_value[0]) == HexByte(0x12));
    REQUIRE(HexByte(attr.intAttribute.attribute_value[1]) == HexByte(0x34));
}

TEST_CASE("Attribute Decoding - OID Type") {
    // Input
    constexpr uint8_t encoded_attr[] = {0x49, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x42, 0x56, 0x78};
    constexpr size_t encoded_size = sizeof(encoded_attr);

    // Output
    Attribute attr{};

    // Decoding
    int res = codecHelper.decode(encoded_attr, encoded_size, &attr, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(attr.type == Attribute::Type::OID);

    uint32_t expected_subids[] = {2, 16, 840, 1, 101, 3, 4, 2, 1};

    REQUIRE(attr.oidAttribute.attribute_type.subids.size() == sizeof(expected_subids) / sizeof(uint32_t));

    for (size_t i = 0; i < attr.oidAttribute.attribute_type.subids.size(); i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(attr.oidAttribute.attribute_type.subids[i] == expected_subids[i]);
    }

    REQUIRE(attr.oidAttribute.attribute_value.size() == 2);
    REQUIRE(HexByte(attr.oidAttribute.attribute_value[0]) == HexByte(0x56));
    REQUIRE(HexByte(attr.oidAttribute.attribute_value[1]) == HexByte(0x78));
}
