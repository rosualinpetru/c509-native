#ifndef __C509_ALGORITHM_IDENTIFIER_H
#define __C509_ALGORITHM_IDENTIFIER_H

#include "structures.hpp"

#include "oid.hpp"

// TODO
#define MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES 128

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
            int16_t intAlgorithmIdentifier; // TODO: could be optimised to uint8_t
            struct
            {
                OID algorithmIdentifier;
                optional<bounded_array<uint8_t, MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES>> parameters;
            } oidAlgorithmIdentifier;
        };
    };
}

#endif // __C509_ALGORITHM_IDENTIFIER_H
