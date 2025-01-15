#ifndef __C509__ATTRIBUTE_H
#define __C509__ATTRIBUTE_H

#include <cstddef>
#include <cstdint>

#include "defs.hpp"
#include "util.hpp"

namespace C509
{
    // WARNING
    constexpr size_t MAX_ATTRIBUTE_VALUE_TSTR_BYTES = 4096;

    // WARNING
    constexpr size_t MAX_ATTRIBUTE_VALUE_BSTR_BYTES = 4096;

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
                const array<uint8_t, MAX_ATTRIBUTE_VALUE_TSTR_BYTES> attributeValue;
            } const intAttribute;

            struct
            {
                const OID attributeType;
                const array<uint8_t, MAX_ATTRIBUTE_VALUE_BSTR_BYTES> attributeValue;
            } const oidAttribute;
        };
    };
}

#endif // __C509__ATTRIBUTE_H