#ifndef __C509_UTIL_H
#define __C509_UTIL_H

#include <cstddef>
#include <cstdint>
#include <cstring>

template <typename T, size_t N>
struct bounded_array
{
    T elements[N];
    size_t len;

    bool copy_from(const T* data, size_t size) {
        if (size > N) return false;
        std::memcpy(elements, data, size * sizeof(T));
        len = size;
        return true;
    }
};

template <typename T>
struct optional {
    bool has_value;
    T value;
};

#endif //__C509_UTIL_H