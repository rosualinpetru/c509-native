#ifndef C509_NAME_H
#define C509_NAME_H

#include <cstdint>

#include "structures.hpp"

#include "attr.hpp"

#define MAX_NAME_ATTRIBUTES 64 // TODO
#define MAX_NAME_RAW 512 // TODO

namespace C509 {
    struct Name {
        enum class Type {
            Attributes,
            TEXT,
            BYTES
        } type;

        union {
            bounded_array<Attribute, MAX_NAME_ATTRIBUTES> attributes;
            bounded_array<uint8_t, MAX_NAME_RAW> raw;
        };
    };
}

#endif // C509_NAME_H
