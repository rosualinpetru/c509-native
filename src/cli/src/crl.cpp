#include <argparse/argparse.hpp>
#include <c509_core/c509.hpp>
#include <file/file_util.hpp>

#include "c509_cli/cli.hpp"

#define MAX_BUFFER_SIZE 16384

int handle_crl(const argparse::ArgumentParser &crl_cmd) {
    const auto gencrl = crl_cmd.get<bool>("-gencrl");
    const auto incrl = crl_cmd.present<std::string>("-incrl");
    const auto revoke = crl_cmd.present<std::string>("-revoke");
    const auto out = crl_cmd.present<std::string>("-out");
    const auto cert = crl_cmd.get<std::string>("-cert");
    const auto keyfile = crl_cmd.get<std::string>("-keyfile");
    const auto compressed = crl_cmd.get<bool>("-compressed");
    const auto days = crl_cmd.get<int>("-crldays");

    uint8_t private_key[MAX_BUFFER_SIZE] = {};
    size_t private_key_size = sizeof(private_key);

    uint8_t ca_buffer[MAX_BUFFER_SIZE] = {};
    size_t ca_buffer_size = sizeof(ca_buffer);

    uint8_t crl_buffer[MAX_BUFFER_SIZE] = {};
    size_t crl_buffer_size = sizeof(crl_buffer);

    read_binary_file(cert, ca_buffer, ca_buffer_size, compressed);
    read_binary_file(keyfile, private_key, private_key_size, compressed);

    if (gencrl)
        crl_gen(private_key, private_key_size, ca_buffer, ca_buffer_size, days, crl_buffer, crl_buffer_size);
    else if (incrl.has_value())
        read_binary_file(incrl.value(), crl_buffer, crl_buffer_size, compressed);
    else {
        std::cerr << "Error: No input provided. Use either the -gencrl or -incrl flag.\n";
        return 1;
    }

    if (revoke.has_value()) {
        uint8_t cert_buffer[MAX_BUFFER_SIZE] = {};
        size_t cert_buffer_size = sizeof(cert_buffer);

        read_binary_file(revoke.value(), cert_buffer, cert_buffer_size, compressed);

        size_t crl_buffer_out_size = sizeof(crl_buffer);
        crl_revoke(private_key, private_key_size, ca_buffer, ca_buffer_size, crl_buffer, crl_buffer_size, cert_buffer,
                   cert_buffer_size, days, crl_buffer, crl_buffer_out_size);
        crl_buffer_size = crl_buffer_out_size;
    }

    if (out.has_value())
        write_binary_file(out.value(), crl_buffer, crl_buffer_size, compressed);

    return 0;
}

void setup_crl_parser(argparse::ArgumentParser &crl_cmd) {
    crl_cmd.add_argument("-gencrl")
            .default_value(false)
            .implicit_value(true)
            .help("Generate a new CRL");

    crl_cmd.add_argument("-incrl")
            .help("Input CRL file (workaround)");

    crl_cmd.add_argument("-revoke")
            .help("Revoke a cert (given in file)");

    crl_cmd.add_argument("-cert")
            .required()
            .help("The CA cert");

    crl_cmd.add_argument("-keyfile")
            .required()
            .help("The CA private key");

    crl_cmd.add_argument("-compressed")
            .default_value(false)
            .implicit_value(true)
            .help("Use Brotli compression");

    crl_cmd.add_argument("-crldays")
            .scan<'i', int>()
            .default_value(30)
            .help("Days until the next CRL is due");

    crl_cmd.add_argument("-out")
            .help("Output file");
}
