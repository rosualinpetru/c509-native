#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <brotli/encode.h>
#include <brotli/decode.h>

#include "file_util.hpp"

void write_binary_file(const std::string &filename, const uint8_t *data, const size_t size, bool compressed) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << "\n";
        exit(-2);
    }

    if (compressed) {
        // Compress data using Brotli
        std::vector<uint8_t> compressed_data(BrotliEncoderMaxCompressedSize(size));
        size_t compressed_size = compressed_data.size();

        if (!BrotliEncoderCompress(
            BROTLI_DEFAULT_QUALITY,
            BROTLI_DEFAULT_WINDOW,
            BROTLI_MODE_GENERIC,
            size,
            data,
            &compressed_size,
            compressed_data.data())) {
            std::cerr << "Error: Brotli compression failed.\n";
            exit(-2);
        }

        // Write the compressed data to file
        file.write(reinterpret_cast<const char *>(compressed_data.data()), compressed_size);
    } else {
        // Write raw data to file
        file.write(reinterpret_cast<const char *>(data), size);
    }


    file.write(reinterpret_cast<const char *>(data), size);
    file.close();
}


void read_binary_file(const std::string &filename, uint8_t *buffer, size_t &size, bool compressed) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error: Could not open file for reading: " << filename << "\n";
        exit(-2);
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> temp_buffer(file_size);
    if (!file.read(reinterpret_cast<char *>(temp_buffer.data()), file_size)) {
        std::cerr << "Error: Could not read file: " << filename << "\n";
        exit(-2);
    }

    file.close();

    if (compressed) {
        size_t decompressed_size = size;
        if (BrotliDecoderDecompress(file_size, temp_buffer.data(), &decompressed_size, buffer) !=
            BROTLI_DECODER_RESULT_SUCCESS) {
            std::cerr << "Error: Brotli decompression failed.\n";
            exit(-2);
        }
        size = decompressed_size;
    } else {
        if (file_size > static_cast<std::streamsize>(size)) {
            std::cerr << "Error: File too large, max allowed size is " << size << " bytes.\n";
            exit(-2);
        }
        std::memcpy(buffer, temp_buffer.data(), file_size);
        size = static_cast<size_t>(file_size);
    }
}
