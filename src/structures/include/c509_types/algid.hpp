#ifndef C509_ALGORITHM_IDENTIFIER_H
#define C509_ALGORITHM_IDENTIFIER_H

#include "structures.hpp"
#include "oid.hpp"

#define MAX_ALGORITHM_IDENTIFIER_PARAMETER_BYTES 128 // TODO

namespace C509 {
    struct AlgorithmIdentifier {
        enum class Type {
            Int,
            OID
        } type{};

        union {
            uint8_t int_algorithm_identifier{};

            struct {
                OID algorithm_identifier;
                optional<bounded_array<uint8_t, MAX_ALGORITHM_IDENTIFIER_PARAMETER_BYTES> > parameters;
            } oid_algorithm_identifier;
        };
    };
}

#endif // C509_ALGORITHM_IDENTIFIER_H
