#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <optional>

#include "c509_core/csr.hpp"

#define MAX_BUFFER_SIZE 16384

void writeBinaryFile(const std::string &filename, const uint8_t *data, size_t size) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << "\n";
        return;
    }
    file.write(reinterpret_cast<const char *>(data), size);
    file.close();

    std::cout << "\nHex dump (" << filename << "):\n";
    for (size_t i = 0; i < size; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<int>(data[i]) << " ";
        if ((i + 1) % 16 == 0) std::cout << '\n';
    }
    std::cout << std::dec << std::endl;
}

std::string getInput(const std::string &prompt, const std::string &defaultValue) {
    std::cout << prompt << " [" << defaultValue << "]: ";
    std::string input;
    std::getline(std::cin, input);
    return input.empty() ? defaultValue : input;
}

std::optional<std::string> getOptionalInput(const std::string &prompt) {
    std::cout << prompt << " (leave blank to skip): ";
    std::string input;
    std::getline(std::cin, input);
    return input.empty() ? std::nullopt : std::optional<std::string>(input);
}

int main(const int argc, char *argv[]) {
    if (argc < 3 || std::string(argv[1]) != "c509" || std::string(argv[2]) != "req") {
        std::cerr << "Usage: c509 req --alg <algorithm>\n";
        return 1;
    }

    std::string algorithm;
    if (argc >= 5 && std::string(argv[3]) == "--alg") {
        algorithm = argv[4];
    } else {
        std::cerr << "Error: Missing --alg <algorithm> argument.\n";
        return 1;
    }

    // Interactive input with default values
    const std::string country = getInput("Country", "US");
    const std::string state = getInput("State", "California");
    const std::string locality = getInput("Locality", "San Francisco");
    const std::string organization = getInput("Organization", "Example Inc.");
    const std::string orgUnit = getInput("Organizational Unit", "Engineering");
    const std::string commonName = getInput("Common Name", "example.com");
    const std::string email = getInput("Email Address", "admin@example.com");
    const std::optional<std::string> challengePassword = getOptionalInput("Challenge Password");

    uint8_t csr_out[MAX_BUFFER_SIZE] = {};
    size_t csr_out_size = MAX_BUFFER_SIZE;
    uint8_t private_key_out[MAX_BUFFER_SIZE] = {};
    size_t private_key_out_size = MAX_BUFFER_SIZE;

    if (!C509::CSR::generate_csr(
        algorithm, country, state, locality, organization, orgUnit,
        commonName, email, challengePassword,
        csr_out, csr_out_size, private_key_out, private_key_out_size)) {
        std::cerr << "Error: CSR generation failed.\n";
        return 1;
    }

    writeBinaryFile("csr_output.bin", csr_out, csr_out_size);
    writeBinaryFile("private_key.bin", private_key_out, private_key_out_size);

    std::cout << "CSR and private key successfully generated and saved!\n";
    return 0;
}
