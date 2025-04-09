#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>

#include "file/file_util.hpp"

#include "c509_core/c509.hpp"

#include "c509_cli/cli.hpp"

#define MAX_BUFFER_SIZE 16384

int handle_genpkey(const argparse::ArgumentParser &genpkey_cmd) {
    const auto algorithm = genpkey_cmd.get<std::string>("-algorithm");
    const auto out_file = genpkey_cmd.get<std::string>("-out");
    const auto compressed = genpkey_cmd.get<bool>("-compressed");

    uint8_t private_key_out[MAX_BUFFER_SIZE] = {};
    size_t private_key_out_size = sizeof(private_key_out);

    if (!key_gen(algorithm, private_key_out, private_key_out_size)) {
        std::cerr << "Error: Key generation failed.\n";
        return 1;
    }

    write_binary_file(out_file, private_key_out, private_key_out_size, compressed);
    return 0;
}

void setup_genpkey_parser(argparse::ArgumentParser &genpkey_cmd) {
    genpkey_cmd.add_argument("-algorithm")
            .required()
            .help("The public key algorithm (some of the algorithms supported by OQS-provider)");

    genpkey_cmd.add_argument("-out")
            .required()
            .help("Output file");

    genpkey_cmd.add_argument("-compressed")
        .default_value(false)
        .implicit_value(true)
        .help("Use Brotli compression");
}
