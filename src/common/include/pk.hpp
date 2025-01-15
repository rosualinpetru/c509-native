#ifndef __C509__SUBJECT_PUBLIC_KEY_H
#define __C509__SUBJECT_PUBLIC_KEY_H

#include <cstdint>

#include "util.hpp"

namespace C509
{
    // WARNING
    // temporary until actually implementing the parsing of pq signatures
    struct SubjectPublicKey
    {
        const array<uint8_t, 32> bytes;
    };
}

#endif // __C509__SUBJECT_PUBLIC_KEY_H