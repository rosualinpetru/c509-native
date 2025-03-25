#ifndef C509_STRUCTURES_H
#define C509_STRUCTURES_H

#include <cstddef>
#include <string>

template<typename T, size_t N>
class bounded_array {
    T elements[N]{};
    size_t len = 0;

public:
    constexpr bounded_array() = default;

    template<size_t M>
    explicit constexpr bounded_array(const T (&data)[M]);

    constexpr bool copy(const T *data, size_t size);

    template<size_t M>
    constexpr bool copy(const T (&data)[M]);

    constexpr size_t size() const;
    static constexpr size_t capacity();
    constexpr void clear();
    constexpr const T &operator[](size_t index) const;
    constexpr T &operator[](size_t index);
    constexpr const T *data() const;
    constexpr size_t *len_p();
    constexpr T *data_p();
    constexpr bool full() const;
    constexpr bool empty() const;

    std::string to_hex_string(size_t start, size_t length) const;
    std::string to_hex_string() const;
    std::string to_utf8_string() const;
};

template<typename T>
class optional {
    bool has_value = false;
    T value;

public:
    constexpr optional() = default;
    explicit constexpr optional(const T &v);
    constexpr void emplace(const T &v);
    constexpr void reset();
    constexpr bool has() const;
    constexpr void set_has();
    constexpr T &get();
    constexpr const T &get() const;
};

#include "structures.tpp"

#endif // C509_STRUCTURES_H
