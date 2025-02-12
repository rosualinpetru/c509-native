#ifndef __C509_ISSUER_SIGNATURE_VALUE_H
#define __C509_ISSUER_SIGNATURE_VALUE_H

#include <cstdint>
#include <array>

namespace C509
{
    // WARNING
    // temporary until actually implementing the parsing of pq signatures
    struct IssuerSignatureValue
    {
        const std::array<uint8_t, 32> bytes;
    };
}

#endif // __C509_ISSUER_SIGNATURE_VALUE_H