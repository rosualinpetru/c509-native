#ifndef C509_ALGORITHM_IDENTIFIER_H
#define C509_ALGORITHM_IDENTIFIER_H

#include "structures.hpp"
#include "oid.hpp"

// Considering only ML-DSA composite, parameters are needed only when combined with RSASSA-PSS
// https://www.ietf.org/archive/id/draft-ietf-lamps-pq-composite-sigs-04.html#name-rsa4096-pss
// Which would be around ~28 bytes of CBOR encoding for the RSA4096-PSS.
#define MAX_ALGORITHM_IDENTIFIER_PARAMETER_BYTES 28

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
                optional<bounded_array<uint8_t, MAX_ALGORITHM_IDENTIFIER_PARAMETER_BYTES>> parameters;
            } oid_algorithm_identifier;
        };

        std::string to_string() const;
    };
}

#endif // C509_ALGORITHM_IDENTIFIER_H
