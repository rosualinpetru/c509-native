#ifndef __C509_ALGORITHM_IDENTIFIER_H
#define __C509_ALGORITHM_IDENTIFIER_H

#include <cstddef>
#include <cstdint>
#include <array>
#include <optional>

#include "oid.hpp"

namespace C509
{
    // WARNING
    constexpr size_t MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES = 512;

    struct AlgorithmIdentifier
    {
        enum class Type
        {
            Int,
            OID
        } const type;

        union
        {
            const uint8_t intAlgorithmIdentifier;
            struct
            {
                const OID algorithmIdentifier;
                const std::optional<std::array<uint8_t, MAX_ALGORITHM_IDENTIFIER_PARMETER_BYTES>> parameters;
            } const oidAlgorithmIdentifier;
        };
    };
}

#endif // __C509_ALGORITHM_IDENTIFIER_H
