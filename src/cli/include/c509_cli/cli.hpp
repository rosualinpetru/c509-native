#ifndef C509_CLI_HPP
#define C509_CLI_HPP

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

Command get_command(const argparse::ArgumentParser &program);

void setup_genpkey_parser(argparse::ArgumentParser &genpkey_cmd);

void setup_req_parser(argparse::ArgumentParser &req_cmd);

int handle_genpkey(const argparse::ArgumentParser &genpkey_cmd);

int handle_req(const argparse::ArgumentParser &req_cmd);

int main(int argc, char *argv[]);

#endif // C509_CLI_HPP
