#include <iostream>
#include <fstream>

#include "file_util.hpp"

void write_binary_file(const std::string &filename, const uint8_t *data, const size_t size) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << "\n";
        exit(-2);
    }
    file.write(reinterpret_cast<const char *>(data), size);
    file.close();
}

void read_binary_file(const std::string &filename, uint8_t *buffer, size_t &size) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error: Could not open file for reading: " << filename << "\n";
        exit(-2);
    }

    // Get file size
    std::streamsize file_size = file.tellg();
    if (file_size > static_cast<std::streamsize>(size)) {
        std::cerr << "Error: File too large, max allowed size is " << size << " bytes.\n";
        exit(-2);
    }

    file.seekg(0, std::ios::beg);

    // Read file content into buffer
    if (!file.read(reinterpret_cast<char *>(buffer), file_size)) {
        std::cerr << "Error: Could not read file: " << filename << "\n";
        exit(-2);
    }

    size = static_cast<size_t>(file_size);
}
