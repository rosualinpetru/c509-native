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
        } type{};

        union {
            struct {
                uint8_t attribute_type; // int32_t if compatibility with re-encoded certs is needed
                bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_TSTR_BYTES> attribute_value;
            } intAttribute;

            struct {
                OID attribute_type;
                bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_BSTR_BYTES> attribute_value;
            } oidAttribute;
        };
    };
}

#endif // C509_ATTRIBUTE_H
