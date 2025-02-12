#ifndef __C509_OID
#define __C509_OID

#include <cstddef>
#include <cstdint>

namespace C509
{
    // Defined in https://datatracker.ietf.org/doc/html/rfc2578#section-3.5
    constexpr size_t MAX_OID_SUBIDS = 128;

    struct OID
    {
        const uint32_t *subids;
        size_t size;
    };
}

#endif // __C509_OID