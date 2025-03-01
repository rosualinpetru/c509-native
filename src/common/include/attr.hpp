#ifndef __C509_ATTRIBUTE_H
#define __C509_ATTRIBUTE_H

#include <cstdint>

#include "structures.hpp"

#include "oid.hpp"

// TODO
#define MAX_ATTRIBUTE_VALUE_TSTR_BYTES 128

// TODO
#define MAX_ATTRIBUTE_VALUE_BSTR_BYTES 128

namespace C509
{
    struct Attribute
    {
        enum class Type
        {
            Int,
            OID
        } type;

        // TODO: Union could be optimised
        union
        {
            struct
            {
                uint8_t attributeType; // TODO: Should be int32_t if compatibility with re-encoded certificates is need.
                bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_TSTR_BYTES> attributeValue;
            } intAttribute;

            struct
            {
                OID attributeType;
                bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_BSTR_BYTES> attributeValue;
            } oidAttribute;
        };
    };
}

#endif // __C509_ATTRIBUTE_H