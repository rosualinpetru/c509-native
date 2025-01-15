#ifndef __C509__ISSUER_SIGNATURE_VALUE_H
#define __C509__ISSUER_SIGNATURE_VALUE_H

#include <cstdint>

#include "util.hpp"

namespace C509
{
    // WARNING
    // temporary until actually implementing the parsing of pq signatures
    struct IssuerSignatureValue
    {
        const array<uint8_t, 32> bytes;
    };
}

#endif // __C509__ISSUER_SIGNATURE_VALUE_H