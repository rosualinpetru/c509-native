#ifndef __C509__NAME_H
#define __C509__NAME_H

#include <cstddef>
#include <cstdint>

#include "attr.hpp"
#include "util.hpp"

namespace C509
{
    // WARNING
    constexpr size_t MAX_NAME_ATTRIBUTES = 32;

    // WARNING
    constexpr size_t MAX_NAME_TSTR_BYTES = 4096;

    // WARNING
    constexpr size_t MAX_NAME_BSTR_BYTES = 4096;

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
            const array<Attribute, MAX_NAME_ATTRIBUTES> attributes;
            const array<uint8_t, MAX_NAME_TSTR_BYTES> text;
            const array<uint8_t, MAX_NAME_BSTR_BYTES> bytes;
        };
    };
}

#endif // __C509__NAME_H