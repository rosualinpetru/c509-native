#ifndef __C509_UTIL_H
#define __C509_UTIL_H

#include <cstddef>
#include <cstdint>

template <typename T, size_t N>
struct array
{
    const T data[N];

    constexpr array(const T (&init)[N]) : data()
    {
        for (size_t i = 0; i < N; ++i)
            const_cast<T &>(data[i]) = init[i];
    }

    constexpr const T &operator[](const size_t index) const
    {
        assert(index < N && "Index out of range");

        return data[index];
    }

    constexpr size_t size() const noexcept
    {
        return N;
    }
};

#endif //__C509_UTIL_H