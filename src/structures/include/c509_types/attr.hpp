#ifndef C509_ATTRIBUTE_H
#define C509_ATTRIBUTE_H

#include <cstdint>

#include "structures.hpp"

#include "oid.hpp"

#define MAX_ATTRIBUTE_VALUE_TSTR_BYTES 128 // TODO
#define MAX_ATTRIBUTE_VALUE_BSTR_BYTES 128 // TODO

namespace C509 {
    struct Attribute {
        enum class Type {
            Unset,
            Int,
            OID
        } type;

        union {
            struct {
                uint8_t attributeType; // int32_t if compatibility with re-encoded certs is needed
                bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_TSTR_BYTES> attributeValue;
            } intAttribute;

            struct {
                OID attributeType;
                bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_BSTR_BYTES> attributeValue;
            } oidAttribute;
        };
    };
}

#endif // C509_ATTRIBUTE_H
