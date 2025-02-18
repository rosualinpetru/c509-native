#ifndef __C509_ATTRIBUTE_H
#define __C509_ATTRIBUTE_H

#include <cstddef>
#include <cstdint>

#include "structures.hpp"
#include "oid.hpp"

// WARNING
#define MAX_ATTRIBUTE_VALUE_TSTR_BYTES 128

// WARNING
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

        union
        {
            struct
            {
                uint8_t attributeType;
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