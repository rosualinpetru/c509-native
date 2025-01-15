#ifndef __C509_DEFINITIONS
#define __C509_DEFINITIONS

#include <stdint.h>

#include "util.hpp"

namespace C509
{
    // WARNING
    // should be in fact 128 as defined by the RFC https://datatracker.ietf.org/doc/html/rfc2578#section-3.5
    constexpr size_t MAX_OID_BYTES = 32;
    using OID = array<uint32_t, MAX_OID_BYTES>;
}

#endif // __C509_DEFINITIONS