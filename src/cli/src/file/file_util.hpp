#ifndef C509_FILE_UTIL_H
#define C509_FILE_UTIL_H

#include <cstdint>

/**
 * @brief Writes binary data to a file, optionally compressing it using Brotli.
 *
 * @param filename The name of the file to write data into.
 * @param data A pointer to the binary data to be written.
 * @param size The size of the data in bytes.
 * @param compressed A boolean flag indicating whether the data should be compressed using Brotli before writing.
 *
 * @details
 * If the `compressed` flag is `true`, the data is compressed using Brotli with default settings
 * before being written to the file. If the compression process fails, the program will log an error
 * message and terminate. If the `compressed` flag is `false`, the raw data is directly written to the file.
 *
 * If the file cannot be opened for writing, the program will log an error message and terminate.
 *
 * @warning This function terminates the program with an error code if either file operations or
 * compression fail.
 */
void write_binary_file(const std::string &filename, const uint8_t *data, size_t size, bool compressed);

/**
 * @brief Reads a binary file into a buffer.
 *
 * This function reads the contents of a binary file and stores it in the provided buffer.
 * Optionally, if the file content is compressed, it decompresses the data using Brotli compression
 * before storing it in the buffer.
 *
 * @param filename The name of the file to read.
 * @param buffer The buffer to store the file contents.
 * @param size Input: Maximum allowed size of data in the buffer. Output: Actual size of the data read or decompressed.
 * @param compressed Indicates whether the file contents are compressed using Brotli.
 *                   If true, the content is decompressed into the buffer.
 *
 * @throw Exit the program with error code -2 in cases such as:
 *        - File cannot be opened for reading.
 *        - File cannot be read.
 *        - Brotli decompression fails when compressed is true.
 *        - File size exceeds the provided buffer size when compressed is false.
 */
void read_binary_file(const std::string &filename, uint8_t *buffer, size_t &size, bool compressed);

#endif // C509_FILE_UTIL_H
