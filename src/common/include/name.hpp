#ifndef __C509_NAME_H
#define __C509_NAME_H

#include <cstddef>
#include <cstdint>

#include "attr.hpp"

namespace C509
{
    // WARNING
    constexpr size_t MAX_NAME_ATTRIBUTES = 16;

    // WARNING
    constexpr size_t MAX_NAME_TSTR_BYTES = 512;

    // WARNING
    constexpr size_t MAX_NAME_BSTR_BYTES = 512;

    struct Name
    {
        enum class Type
        {
            ATTRIBUTES,
            TEXT,
            BYTES
        } const type;

        union
        {
            const std::array<Attribute, MAX_NAME_ATTRIBUTES> attributes;
            const std::array<uint8_t, MAX_NAME_TSTR_BYTES> text;
            const std::array<uint8_t, MAX_NAME_BSTR_BYTES> bytes;
        };
    };
}

#endif // __C509_NAME_H