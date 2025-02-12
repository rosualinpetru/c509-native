#ifndef __C509_SUBJECT_PUBLIC_KEY_H
#define __C509_SUBJECT_PUBLIC_KEY_H

#include <cstdint>
#include <array>

namespace C509
{
    // WARNING
    // temporary until actually implementing the parsing of pq signatures
    struct SubjectPublicKey
    {
        const std::array<uint8_t, 32> bytes;
    };
}

#endif // __C509_SUBJECT_PUBLIC_KEY_H