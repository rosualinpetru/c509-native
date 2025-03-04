#ifndef C509_STRUCTURES_H
#define C509_STRUCTURES_H

#include <cstddef>

template<typename T, size_t N>
class bounded_array {
    T elements[N];
    size_t len = 0;

public:
    constexpr bounded_array() = default;

    template<size_t M>
    explicit constexpr bounded_array(const T (&data)[M]) {
        static_assert(M <= N, "Array size exceeds bounded_array capacity!");
        copy(data, M);
    }

    constexpr bool copy(const T *data, const size_t size) {
        if (size > N) return false;
        for (size_t i = 0; i < size; ++i)
            elements[i] = data[i];
        len = size;
        return true;
    }

    template<size_t M>
    constexpr bool copy(const T (&data)[M]) {
        static_assert(M <= N, "Array size exceeds bounded_array capacity!");
        return copy(data, M);
    }

    constexpr size_t size() const {
        return len;
    }

    static constexpr size_t capacity() {
        return N;
    }

    constexpr void clear() {
        len = 0;
    }

    constexpr const T &operator[](size_t index) const {
        return elements[index];
    }

    constexpr T &operator[](size_t index) {
        return elements[index];
    }

    constexpr const T *data() const {
        return elements;
    }

    constexpr size_t *len_p() {
        return &len;
    }

    constexpr T *data_p() {
        return elements;
    }

    constexpr bool full() const {
        return len == N;
    }

    constexpr bool empty() const {
        return len == 0;
    }
};

template<typename T>
class optional {
    bool has_value = false;
    T value;

public:
    constexpr optional() = default;

    explicit constexpr optional(const T &v) : has_value(true), value(v) {
    }

    constexpr void emplace(const T &v) {
        value = v;
        has_value = true;
    }

    constexpr void reset() {
        has_value = false;
    }

    constexpr bool has() const {
        return has_value;
    }

    constexpr void set_has() {
        has_value = true;
    }

    constexpr T &get() {
        return value;
    }

    constexpr const T &get() const {
        return value;
    }
};

#endif // C509_STRUCTURES_H
