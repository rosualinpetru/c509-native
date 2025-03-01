#ifndef __C509_NAME_H
#define __C509_NAME_H

#include <cstdint>

#include "structures.hpp"

#include "attr.hpp"

// TODO
#define MAX_NAME_ATTRIBUTES 64
// TODO
#define MAX_NAME_TSTR_BYTES 512
// TODO
#define MAX_NAME_BSTR_BYTES 512

namespace C509
{
    struct Name
    {
        enum class Type
        {
            ATTRIBUTES,
            TEXT,
            BYTES
        } type;

        union
        {
            bounded_array<Attribute, MAX_NAME_ATTRIBUTES> attributes;
            bounded_array<uint8_t, MAX_NAME_TSTR_BYTES> text;
            bounded_array<uint8_t, MAX_NAME_BSTR_BYTES> bytes;
        };
    };
}

#endif // __C509_NAME_H