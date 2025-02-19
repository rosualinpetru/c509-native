#ifndef __C509_SUBJECT_PUBLIC_KEY_H
#define __C509_SUBJECT_PUBLIC_KEY_H

#include "structures.hpp"

namespace C509
{
    // WARNING
    // temporary until actually implementing the parsing of pq signatures
    struct SubjectPublicKey
    {
        const bounded_array<uint8_t, 32> bytes;
    };
}

#endif // __C509_SUBJECT_PUBLIC_KEY_H