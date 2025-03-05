#ifndef C509_FILE_UTIL_H
#define C509_FILE_UTIL_H

#include <iostream>
#include <fstream>
#include <cstdint>

void write_binary_file(const std::string &filename, const uint8_t *data, const size_t size) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << "\n";
        exit(-2);
    }
    file.write(reinterpret_cast<const char *>(data), size);
    file.close();
}

#endif // C509_FILE_UTIL_H
