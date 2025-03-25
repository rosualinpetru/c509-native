#ifndef C509_NAME_H
#define C509_NAME_H

#include <cstdint>
#include <string>

#include "structures.hpp"

#include "attr.hpp"

#define MAX_NAME_ATTRIBUTES 32 // https://datatracker.ietf.org/doc/html/rfc5280#section-4.1.2.4, (1..MAX), consider MAX = 32 (number of attributes in the C509 registry)
#define MAX_NAME_RAW 64 // https://datatracker.ietf.org/doc/html/rfc5280#appendix-A.1, upper bounds ub-common-name-length

namespace C509 {
    struct Name {
        enum class Type {
            Attributes,
            Text,
            Bytes
        } type{};

        union {
            bounded_array<Attribute, MAX_NAME_ATTRIBUTES> attributes{};
            bounded_array<uint8_t, MAX_NAME_RAW> raw;
        };

        std::string to_string() const;
    };
}

#endif // C509_NAME_H
