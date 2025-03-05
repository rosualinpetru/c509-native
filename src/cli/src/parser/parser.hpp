#ifndef C509_PARSER_H
#define C509_PARSER_H

#include <string>
#include <argparse/argparse.hpp>
#include <c509_core/c509.hpp>

#define CLI_NAME "c509_cli"
#define GENPKEY_CMD "genpkey"
#define REQ_CMD "req"
#define CRL_CMD "crl"

enum class Command {
    GENPKEY,
    REQ,
    CRL,
    UNKNOWN
};

Command get_command(const argparse::ArgumentParser &program) {
    try {
        if (program.is_subcommand_used(GENPKEY_CMD)) return Command::GENPKEY;
        if (program.is_subcommand_used(REQ_CMD)) return Command::REQ;
        if (program.is_subcommand_used(CRL_CMD)) return Command::CRL;
    } catch (const std::exception &_) {
    }
    return Command::UNKNOWN;
}

void setup_genpkey_parser(argparse::ArgumentParser &genpkey_cmd) {
    std::string algorithms;
    for (auto it = C509::valid_algorithms.begin(); it != C509::valid_algorithms.end(); ++it) {
        if (!algorithms.empty()) {
            algorithms += ", ";
        }
        algorithms += it->first;
    }

    genpkey_cmd.add_argument("-algorithm")
            .required()
            .help("The public key algorithm (" + algorithms + ")");

    genpkey_cmd.add_argument("-out")
            .required()
            .help("Output file");
}

void setup_req_parser(argparse::ArgumentParser &req_cmd) {
    // General options
    req_cmd.add_argument("-in")
            .help("C509 request input file");

    req_cmd.add_argument("-verify")
            .default_value(false)
            .implicit_value(true)
            .help("Verify self-signature on the request");

    // Certificate options
    req_cmd.add_argument("-new")
            .default_value(false)
            .implicit_value(true)
            .help("New request");

    req_cmd.add_argument("-c509")
            .default_value(false)
            .implicit_value(true)
            .help("Output an C509 certificate structure instead of a cert request");

    req_cmd.add_argument("-CA")
            .help("Issuer cert to use for signing a cert, implies -c509");

    req_cmd.add_argument("-CAkey")
            .help("Issuer private key to use with -CA; default is -CA arg");

    req_cmd.add_argument("-subj")
            .required()
            .help("Specify the subject (Distinguished Name) in OpenSSL format: "
                "\"/C=XX/ST=State/L=City/O=Organization/OU=OrgUnit/CN=CommonName/emailAddress=email@example.com\".");

    req_cmd.add_argument("-days")
            .scan<'i', int>()
            .default_value(365)
            .help("Number of days cert is valid for. Default: 365 days");

    req_cmd.add_argument("-set_serial")
            .scan<'i', int>()
            .help("Serial number to use");

    req_cmd.add_argument("-addext")
            .nargs(argparse::nargs_pattern::any)
            .help("Additional cert extension key=value pair (may be given more than once)");

    // Keys & Signing
    req_cmd.add_argument("-key")
            .required()
            .help("Key for signing, and to include unless -in given");

    // Output
    req_cmd.add_argument("-out")
            .required()
            .help("Output file");

    req_cmd.add_argument("-batch")
            .default_value(false)
            .implicit_value(true)
            .help("Do not ask anything during request generation");
}

#endif // C509_PARSER_H
