#ifndef __C509_OID
#define __C509_OID

#include "structures.hpp"

// Defined in https://datatracker.ietf.org/doc/html/rfc2578#section-3.5
#define MAX_OID_SUBIDS 128

namespace C509
{
    struct OID
    {
        bounded_array<uint32_t, MAX_OID_SUBIDS> subids;
    };
}

#endif // __C509_OID