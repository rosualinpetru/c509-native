#ifndef BOUNDED_STRUCTURES_TPP
#define BOUNDED_STRUCTURES_TPP

#include "c509_types/structures.hpp"

#include <iomanip>

template<typename T, size_t N>
template<size_t M>
constexpr bounded_array<T, N>::bounded_array(const T (&data)[M]) {
    static_assert(M <= N, "Array size exceeds bounded_array capacity!");
    copy(data, M);
}

template<typename T, size_t N>
template<size_t M>
constexpr bool bounded_array<T, N>::copy(const T (&data)[M]) {
    static_assert(M <= N, "Array size exceeds bounded_array capacity!");
    return copy(data, M);
}

template<typename T, size_t N>
constexpr bool bounded_array<T, N>::copy(const T *data, const size_t size) {
    if (size > N) return false;
    for (size_t i = 0; i < size; ++i)
        elements[i] = data[i];
    len = size;
    return true;
}

template<typename T, size_t N>
constexpr size_t bounded_array<T, N>::size() const {
    return len;
}

template<typename T, size_t N>
constexpr size_t bounded_array<T, N>::capacity() {
    return N;
}

template<typename T, size_t N>
constexpr void bounded_array<T, N>::clear() {
    len = 0;
}

template<typename T, size_t N>
constexpr const T &bounded_array<T, N>::operator[](size_t index) const {
    return elements[index];
}

template<typename T, size_t N>
constexpr T &bounded_array<T, N>::operator[](size_t index) {
    return elements[index];
}

template<typename T, size_t N>
constexpr const T *bounded_array<T, N>::data() const {
    return elements;
}

template<typename T, size_t N>
constexpr size_t *bounded_array<T, N>::len_p() {
    return &len;
}

template<typename T, size_t N>
constexpr T *bounded_array<T, N>::data_p() {
    return elements;
}

template<typename T, size_t N>
constexpr bool bounded_array<T, N>::full() const {
    return len == N;
}

template<typename T, size_t N>
constexpr bool bounded_array<T, N>::empty() const {
    return len == 0;
}

template<typename T, size_t N>
std::string bounded_array<T, N>::to_hex_string(size_t start, size_t length) const {
    std::ostringstream oss;
    for (size_t i = start; i < start + length && i < size(); ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(elements[i]);
        if (i < start + length - 1) {
            oss << " ";
        }
    }
    return oss.str();
}

template<typename T, size_t N>
std::string bounded_array<T, N>::to_hex_string() const {
    return to_hex_string(0, size());
}

template<typename T, size_t N>
std::string bounded_array<T, N>::to_utf8_string() const {
    return std::string(reinterpret_cast<const char *>(elements), size());
}

template<typename T>
constexpr optional<T>::optional(const T &v) : has_value(true), value(v) {
}

template<typename T>
constexpr void optional<T>::emplace(const T &v) {
    value = v;
    has_value = true;
}

template<typename T>
constexpr void optional<T>::reset() {
    has_value = false;
}

template<typename T>
constexpr bool optional<T>::has() const {
    return has_value;
}

template<typename T>
constexpr void optional<T>::set_has() {
    has_value = true;
}

template<typename T>
constexpr T &optional<T>::get() {
    return value;
}

template<typename T>
constexpr const T &optional<T>::get() const {
    return value;
}

#endif // BOUNDED_STRUCTURES_TPP
