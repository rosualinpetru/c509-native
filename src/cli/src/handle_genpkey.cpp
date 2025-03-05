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

    uint8_t private_key_out[MAX_BUFFER_SIZE] = {};
    size_t private_key_out_size = sizeof(private_key_out);

    if (!C509::keygen(algorithm, private_key_out, private_key_out_size)) {
        std::cerr << "Error: Key generation failed.\n";
        return 1;
    }

    write_binary_file(out_file, private_key_out, private_key_out_size);
    return 0;
}
