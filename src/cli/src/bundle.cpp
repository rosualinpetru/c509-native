#include <iostream>
#include <argparse/argparse.hpp>

#include "c509_codec/codec.hpp"

#include "c509_core/c509.hpp"

#include "c509_cli/cli.hpp"

#include "file/file_util.hpp"

#define MAX_BUFFER_SIZE 16384
#define MAX_BUNDLE_SIZE (MAX_BUFFER_SIZE * MAX_C509_BAG)


int handle_bundle(const argparse::ArgumentParser &bundle_cmd) {
    const auto input_files = bundle_cmd.get<std::vector<std::string> >("-in");
    const auto output_file = bundle_cmd.get<std::string>("-out");
    const auto compression = bundle_cmd.get<bool>("-compressed");

    uint8_t cert_buffer[MAX_BUFFER_SIZE] = {};

    C509::COSE_C509 bundle;

    for (const auto &file: input_files) {
        size_t cert_buffer_size = sizeof(cert_buffer);
        read_binary_file(file, cert_buffer, cert_buffer_size, compression);

        if (cbor_decode(cert_buffer, cert_buffer_size, &bundle.certificates[(*bundle.certificates.len_p())++], nullptr) != 0) {
            std::cerr << "Error: Failed to parse ca cert.\n";
            return false;
        }
    }

    uint8_t bundle_buffer[MAX_BUNDLE_SIZE] = {};
    size_t bundle_buffer_size = sizeof(bundle_buffer);


    if (cbor_encode(bundle_buffer, bundle_buffer_size, &bundle, &bundle_buffer_size) != 0) {
        std::cerr << "Error: Failed to create COSE_C509 bundle." << std::endl;
        return 1;
    }

    write_binary_file(output_file, bundle_buffer, bundle_buffer_size, compression);

    return 0;
}

void setup_bundle_parser(argparse::ArgumentParser &bundle_cmd) {
    bundle_cmd.add_argument("-in")
            .required()
            .nargs(1, MAX_C509_BAG)
            .help("Input certificates");

    bundle_cmd.add_argument("-out")
            .required()
            .help("Output file");

    bundle_cmd.add_argument("-compressed")
            .default_value(false)
            .implicit_value(true)
            .help("Use Brotli compression");
}
