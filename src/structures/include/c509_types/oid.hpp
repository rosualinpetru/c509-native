#ifndef C509_OID_H
#define C509_OID_H

#include <cstdint>
#include <string>

#include "structures.hpp"

// https://datatracker.ietf.org/doc/html/rfc5280#appendix-B, see paragraph on arc
#define MAX_OID_SUBIDS 20

namespace C509 {
    struct OID {
        bounded_array<uint32_t, MAX_OID_SUBIDS> subids;

        OID();

        OID(const uint32_t *data, size_t size);

        bool operator==(const OID &other) const;

        std::string to_string() const;
    };
}

#endif // C509_OID_H
