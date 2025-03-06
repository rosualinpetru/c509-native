#ifndef C509_FILE_UTIL_H
#define C509_FILE_UTIL_H

#include <cstdint>

void write_binary_file(const std::string &filename, const uint8_t *data, size_t size);
void read_binary_file(const std::string &filename, uint8_t *buffer, size_t &size);

#endif // C509_FILE_UTIL_H
