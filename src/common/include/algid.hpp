#ifndef __C509_ALGORITHM_IDENTIFIER_H
#define __C509_ALGORITHM_IDENTIFIER_H

#include <cstddef>
#include <cstdint>

#include "oid.hpp"
#include "structures.hpp"

#define MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES 512

namespace C509
{
    struct AlgorithmIdentifier
    {
        enum class Type
        {
            Int,
            OID
        } type;

        union
        {
            int16_t intAlgorithmIdentifier;
            struct
            {
                OID algorithmIdentifier;
                optional<bounded_array<uint8_t, MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES>> parameters;
            } oidAlgorithmIdentifier;
        };
    };
}

#endif // __C509_ALGORITHM_IDENTIFIER_H
