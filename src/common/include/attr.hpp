#ifndef __C509_ATTRIBUTE_H
#define __C509_ATTRIBUTE_H

#include <cstddef>
#include <cstdint>
#include <array>

#include "oid.hpp"

namespace C509
{
    // WARNING
    constexpr size_t MAX_ATTRIBUTE_VALUE_TSTR_BYTES = 256;

    // WARNING
    constexpr size_t MAX_ATTRIBUTE_VALUE_BSTR_BYTES = 256;

    struct Attribute
    {
        enum class Type
        {
            Int,
            OID
        } const type;

        union
        {
            struct
            {
                const uint8_t attributeType;
                const std::array<uint8_t, MAX_ATTRIBUTE_VALUE_TSTR_BYTES> attributeValue;
            } const intAttribute;

            struct
            {
                const OID attributeType;
                const std::array<uint8_t, MAX_ATTRIBUTE_VALUE_BSTR_BYTES> attributeValue;
            } const oidAttribute;
        };
    };
}

#endif // __C509_ATTRIBUTE_H