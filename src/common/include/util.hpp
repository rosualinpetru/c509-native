#ifndef __C509_UTIL_H
#define __C509_UTIL_H

#include <cstddef>
#include <cstdint>

template <typename T, size_t N>
struct bounded_array
{
    const T elements[N];
    const size_t len;
};

#endif //__C509_UTIL_H