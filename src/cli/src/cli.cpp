#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

#include "parser/parser.hpp"

#include "c509_cli/cli.hpp"

int main(const int argc, char *argv[]) {
    // Create the main parser
    argparse::ArgumentParser program(CLI_NAME);

    // Create individual parsers for each command
    argparse::ArgumentParser genpkey_cmd(GENPKEY_CMD);
    setup_genpkey_parser(genpkey_cmd);

    argparse::ArgumentParser req_cmd(REQ_CMD);
    setup_req_parser(req_cmd);

    // Register subcommands
    program.add_subparser(genpkey_cmd);
    program.add_subparser(req_cmd);

    if (argc == 1) {
        std::cout << program;
        return 1;
    }

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &err) {
        switch (get_command(program)) {
            case Command::GENPKEY:
                std::cout << genpkey_cmd;
                break;
            case Command::REQ:
                std::cout << req_cmd;
                break;
            case Command::UNKNOWN:
            default:
                std::cout << program;
        }
        if (argc > 2)
            std::cerr << "\nError: " << err.what() << "\n";
        return 1;
    }

    switch (get_command(program)) {
        case Command::GENPKEY:
            return handle_genpkey(genpkey_cmd);
        case Command::REQ:
            std::cerr << "Error: command is not implemented yet.\n";
            return 1;
        case Command::CRL:
            std::cerr << "Error: command is not implemented yet.\n";
            return 1;
        case Command::UNKNOWN:
        default:
            return 1;
    }
}


//
//
// #include <iostream>
// #include <fstream>
// #include <iomanip>
// #include <string>
// #include <optional>
//
// #include "c509_core/csr.hpp"
//
// #define MAX_BUFFER_SIZE 16384
//
// void writeBinaryFile(const std::string &filename, const uint8_t *data, const size_t size) {
//     std::ofstream file(filename, std::ios::binary);
//     if (!file) {
//         std::cerr << "Error: Could not open file for writing: " << filename << "\n";
//         return;
//     }
//     file.write(reinterpret_cast<const char *>(data), size);
//     file.close();
//
//     std::cout << "\nHex dump (" << filename << "):\n";
//     for (size_t i = 0; i < size; ++i) {
//         std::cout << std::hex << std::setw(2) << std::setfill('0')
//                   << static_cast<int>(data[i]) << " ";
//         if ((i + 1) % 16 == 0) std::cout << '\n';
//     }
//     std::cout << std::dec << std::endl;
// }
//
// std::string getInput(const std::string &prompt, const std::string &defaultValue) {
//     std::cout << prompt << " [" << defaultValue << "]: ";
//     std::string input;
//     std::getline(std::cin, input);
//     return input.empty() ? defaultValue : input;
// }
//
// std::optional<std::string> getOptionalInput(const std::string &prompt) {
//     std::cout << prompt << " (leave blank to skip): ";
//     std::string input;
//     std::getline(std::cin, input);
//     return input.empty() ? std::nullopt : std::optional<std::string>(input);
// }
//
// int main(const int argc, char *argv[]) {
//     if (argc < 7 || std::string(argv[1]) != "c509" || std::string(argv[2]) != "req" || std::string(argv[3]) != "--alg") {
//         std::cerr << "Usage: c509 req --alg <algorithm> --out-csr <csr_file> --out-key <key_file>\n";
//         return 1;
//     }
//
//     std::string algorithm = argv[4];
//     std::string csr_filename;
//     std::string key_filename;
//
//     for (int i = 5; i < argc; i++) {
//         if (std::string(argv[i]) == "--out-csr" && i + 1 < argc) {
//             csr_filename = argv[i + 1];
//         } else if (std::string(argv[i]) == "--out-key" && i + 1 < argc) {
//             key_filename = argv[i + 1];
//         }
//     }
//
//     if (csr_filename.empty() || key_filename.empty()) {
//         std::cerr << "Error: Missing output file paths for CSR and/or private key.\n";
//         return 1;
//     }
//
//     // Interactive input with default values
//     const std::string country = getInput("Country", "US");
//     const std::string state = getInput("State", "California");
//     const std::string locality = getInput("Locality", "San Francisco");
//     const std::string organization = getInput("Organization", "Example Inc.");
//     const std::string orgUnit = getInput("Organizational Unit", "Engineering");
//     const std::string commonName = getInput("Common Name", "example.com");
//     const std::string email = getInput("Email Address", "admin@example.com");
//     const std::optional<std::string> challengePassword = getOptionalInput("Challenge Password");
//
//     uint8_t csr_out[MAX_BUFFER_SIZE] = {};
//     size_t csr_out_size = MAX_BUFFER_SIZE;
//     uint8_t private_key_out[MAX_BUFFER_SIZE] = {};
//     size_t private_key_out_size = MAX_BUFFER_SIZE;
//
//     if (!C509::CSR::generate_csr(
//         algorithm, country, state, locality, organization, orgUnit,
//         commonName, email, challengePassword,
//         csr_out, csr_out_size, private_key_out, private_key_out_size)) {
//         std::cerr << "Error: CSR generation failed.\n";
//         return 1;
//     }
//
//     writeBinaryFile(csr_filename, csr_out, csr_out_size);
//     writeBinaryFile(key_filename, private_key_out, private_key_out_size);
//
//     std::cout << "CSR and private key successfully generated and saved!\n";
//     return 0;
// }
