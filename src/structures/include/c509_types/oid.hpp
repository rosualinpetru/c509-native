#ifndef C509_OID_H
#define C509_OID_H

#include <cstdint>

#include "structures.hpp"

// Defined in https://datatracker.ietf.org/doc/html/rfc2578#section-3.5
#define MAX_OID_SUBIDS 128

namespace C509 {
    struct OID {
        bounded_array<uint32_t, MAX_OID_SUBIDS> subids;

        constexpr bool operator==(const OID &other) const {
            if (subids.size() != other.subids.size()) return false;
            for (size_t i = 0; i < subids.size(); ++i)
                if (subids[i] != other.subids[i]) return false;
            return true;
        }
    };
}

#endif // C509_OID_H
