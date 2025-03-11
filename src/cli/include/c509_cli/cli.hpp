#ifndef C509_CLI_HPP
#define C509_CLI_HPP

#define CLI_NAME "c509_cli"

#define GENPKEY_CMD "genpkey"
#define REQ_CMD "req"
#define C509_CMD "c509"
#define CRL_CMD "crl"
#define BUNDLE_CMD "bundle"

enum class Command {
    GENPKEY,
    REQ,
    C509,
    CRL,
    BUNDLE,
    UNKNOWN
};

Command get_command(const argparse::ArgumentParser &program);

void setup_genpkey_parser(argparse::ArgumentParser &genpkey_cmd);

void setup_req_parser(argparse::ArgumentParser &req_cmd);

void setup_bundle_parser(argparse::ArgumentParser &bundle_cmd);

void setup_crl_parser(argparse::ArgumentParser &crl_cmd);

int handle_genpkey(const argparse::ArgumentParser &genpkey_cmd);

int handle_req(const argparse::ArgumentParser &req_cmd);

int handle_bundle(const argparse::ArgumentParser &bundle_cmd);

int handle_crl(const argparse::ArgumentParser &crl_cmd);

int main(int argc, char *argv[]);

#endif // C509_CLI_HPP
