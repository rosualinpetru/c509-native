#include <iostream>
#include <argparse/argparse.hpp>

#include "c509_codec/codec.hpp"

#include "c509_core/c509.hpp"

#include "c509_cli/cli.hpp"

#include "file/file_util.hpp"

#define MAX_BUFFER_SIZE 16384
#define MAX_BUNDLE_SIZE (MAX_BUFFER_SIZE * MAX_C509_BAG)

template<typename T>
bool try_parse(uint8_t *buffer, const size_t max_buffer_size) {
    T data{};

    if (cbor_decode(buffer, max_buffer_size, &data, nullptr) != 0)
        return false;

    std::cout << data.to_string() << std::endl;
    return true;
}

int handle_parse(const argparse::ArgumentParser &parse_cmd) {
    const auto in = parse_cmd.get<std::string>("-in");
    const auto compression = parse_cmd.get<bool>("-compressed");

    size_t size = MAX_BUFFER_SIZE;
    uint8_t buffer[MAX_BUFFER_SIZE] = {};


    read_binary_file(in, buffer, size, compression);

    if (try_parse<C509::C509PrivateKey>(buffer, size))
        return 0;

    if (try_parse<C509::C509Certificate>(buffer, size))
        return 0;

    if (try_parse<C509::CSR::C509CertificateRequest>(buffer, size))
        return 0;

    if (try_parse<C509::CRL::C509CertificateRevocationList>(buffer, size))
        return 0;

    if (try_parse<C509::COSE_C509>(buffer, size))
        return 0;

    return 1;
}

void setup_parse_parser(argparse::ArgumentParser &parse_cmd) {
    parse_cmd.add_argument("-in")
            .required()
            .help("C509 request input file");

    parse_cmd.add_argument("-compressed")
            .default_value(false)
            .implicit_value(true)
            .help("Use Brotli compression");
}
