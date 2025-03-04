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
        } type;

        union {
            uint8_t intAlgorithmIdentifier;

            struct {
                OID algorithmIdentifier;
                optional<bounded_array<uint8_t, MAX_ALGORITHM_IDENTIFIER_PARAMETER_BYTES> > parameters;
            } oidAlgorithmIdentifier;
        };
    };
}

#endif // C509_ALGORITHM_IDENTIFIER_H
