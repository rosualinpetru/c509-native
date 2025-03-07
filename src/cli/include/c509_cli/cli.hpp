#ifndef C509_CLI_HPP
#define C509_CLI_HPP

#define CLI_NAME "c509_cli"

#define GENPKEY_CMD "genpkey"
#define REQ_CMD "req"
#define C509_CMD "c509"
#define CRL_CMD "crl"

enum class Command {
    GENPKEY,
    REQ,
    C509,
    CRL,
    UNKNOWN
};

Command get_command(const argparse::ArgumentParser &program);

void setup_genpkey_parser(argparse::ArgumentParser &genpkey_cmd);

void setup_req_parser(argparse::ArgumentParser &req_cmd);

int handle_genpkey(const argparse::ArgumentParser &genpkey_cmd);

int handle_req(const argparse::ArgumentParser &req_cmd);

int main(int argc, char *argv[]);

#endif // C509_CLI_HPP
