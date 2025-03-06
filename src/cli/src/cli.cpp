#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

#include "c509_cli/cli.hpp"

inline Command get_command(const argparse::ArgumentParser &program) {
    try {
        if (program.is_subcommand_used(GENPKEY_CMD)) return Command::GENPKEY;
        if (program.is_subcommand_used(REQ_CMD)) return Command::REQ;
        if (program.is_subcommand_used(CRL_CMD)) return Command::CRL;
    } catch (const std::exception &_) {
    }
    return Command::UNKNOWN;
}

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
            if (argc == 2) {
                std::cout << req_cmd;
                return 0;
            }
            return handle_req(req_cmd);
        case Command::CRL:
            std::cerr << "Error: command is not implemented yet.\n";
            return 1;
        case Command::UNKNOWN:
        default:
            return 1;
    }
}
