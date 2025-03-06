#include <catch2/catch_test_macros.hpp>

#include "test_helper.cpp"

using namespace C509;

static auto codecHelper = CodecTestHelper(4, 1, reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Name>::encode),
                                          reinterpret_cast<zcbor_decoder_t *>(CBORCodec<Name>::decode));

TEST_CASE("Name Encoding - Attributes Type") {
    // Input
    Name name{};
    name.type = Name::Type::Attributes;

    *name.attributes.len_p() = 2;

    Attribute *attr1 = &name.attributes[0];
    Attribute *attr2 = &name.attributes[1];

    attr1->type = Attribute::Type::Int;
    attr1->intAttribute.attribute_type = 42;
    attr1->intAttribute.attribute_value.copy({0x12, 0x34});

    attr2->type = Attribute::Type::OID;
    attr2->oidAttribute.attribute_type.subids.copy({2, 16, 840});
    attr2->oidAttribute.attribute_value.copy({0x56, 0x78, 0x99});

    // Output
    uint8_t out[MAX_NAME_RAW];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, sizeof(out), &name, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    const uint8_t expected_result[] = {
        0x84, 0x18, 0x2a, 0x62, 0x12, 0x34, 0x43, 0x60, 0x86, 0x48, 0x43, 0x56, 0x78, 0x99
    };

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Name Encoding - Text Type") {
    // Input
    Name name{};
    name.type = Name::Type::Text;
    const auto text = "Test Name";
    name.raw.copy(reinterpret_cast<const uint8_t *>(text), strlen(text));

    // Output
    uint8_t out[MAX_NAME_RAW];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, sizeof(out), &name, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    constexpr uint8_t expected_result[] = {0x69, 'T', 'e', 's', 't', ' ', 'N', 'a', 'm', 'e'};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Name Encoding - Bytes Type") {
    // Input
    Name name{};
    name.type = Name::Type::Bytes;
    name.raw.copy({0xab, 0xcd, 0xef});

    // Output
    uint8_t out[MAX_NAME_RAW];
    size_t out_size;

    // Encoding
    const int res = codecHelper.encode(out, sizeof(out), &name, &out_size);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);

    constexpr uint8_t expected_result[] = {0x43, 0xab, 0xcd, 0xef};

    REQUIRE(out_size == sizeof(expected_result));

    for (int i = 0; i < out_size; i++)
    SECTION("Checking index " + std::to_string(i)) {
        REQUIRE(HexByte(out[i]) == HexByte(expected_result[i]));
    }
}

TEST_CASE("Name Decoding - Attributes Type") {
    // Input
    constexpr uint8_t encoded_name[] = {
        0x84, 0x18, 0x2a, 0x62, 0x12, 0x34, 0x43, 0x60, 0x86, 0x48, 0x43, 0x56, 0x78, 0x99
    };
    constexpr size_t encoded_size = sizeof(encoded_name);

    // Output
    Name name{};

    // Decoding
    const int res = codecHelper.decode(encoded_name, encoded_size, &name, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(name.type == Name::Type::Attributes);
    REQUIRE(name.attributes.size() == 2);
    REQUIRE(name.attributes[0].type == Attribute::Type::Int);
    REQUIRE(name.attributes[1].type == Attribute::Type::OID);
}

TEST_CASE("Name Decoding - Text Type") {
    // Input
    constexpr uint8_t encoded_name[] = {0x69, 'T', 'e', 's', 't', ' ', 'N', 'a', 'm', 'e'};
    constexpr size_t encoded_size = sizeof(encoded_name);

    // Output
    Name name{};

    // Decoding
    const int res = codecHelper.decode(encoded_name, encoded_size, &name, nullptr);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(name.type == Name::Type::Text);
    REQUIRE(strncmp(reinterpret_cast<const char *>(name.raw.data()), "Test Name", name.raw.size()) == 0);
}

TEST_CASE("Name Decoding - Bytes Type") {
    // Input
    constexpr uint8_t encoded_name[] = {0x43, 0xAB, 0xCD, 0xEF};
    constexpr size_t encoded_size = sizeof(encoded_name);

    // Output
    Name name{};

    // Decoding
    const int res = codecHelper.decode(encoded_name, encoded_size, &name, NULL);

    // Assertions
    REQUIRE(res == ZCBOR_SUCCESS);
    REQUIRE(name.type == Name::Type::Bytes);
    REQUIRE(name.raw.size() == 3);
    REQUIRE(name.raw[0] == 0xAB);
    REQUIRE(name.raw[1] == 0xCD);
    REQUIRE(name.raw[2] == 0xEF);
}
