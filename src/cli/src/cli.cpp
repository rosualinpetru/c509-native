#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

#include "c509_cli/cli.hpp"

inline Command get_command(const argparse::ArgumentParser &program) {
    try {
        if (program.is_subcommand_used(GENPKEY_CMD)) return Command::GENPKEY;
        if (program.is_subcommand_used(REQ_CMD)) return Command::REQ;
        if (program.is_subcommand_used(CRL_CMD)) return Command::CRL;
        if (program.is_subcommand_used(BUNDLE_CMD)) return Command::BUNDLE;
        if (program.is_subcommand_used(PARSE_CMD)) return Command::PARSE;
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
    program.add_subparser(genpkey_cmd);

    argparse::ArgumentParser req_cmd(REQ_CMD);
    setup_req_parser(req_cmd);
    program.add_subparser(req_cmd);

    argparse::ArgumentParser crl_cmd(CRL_CMD);
    setup_crl_parser(crl_cmd);
    program.add_subparser(crl_cmd);

    argparse::ArgumentParser bundle_cmd(BUNDLE_CMD);
    setup_bundle_parser(bundle_cmd);
    program.add_subparser(bundle_cmd);

    argparse::ArgumentParser parse_cmd(PARSE_CMD);
    setup_parse_parser(parse_cmd);
    program.add_subparser(parse_cmd);

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
            case Command::CRL:
                std::cout << crl_cmd;
                break;
            case Command::BUNDLE:
                std::cout << bundle_cmd;
                break;
            case Command::PARSE:
                std::cout << parse_cmd;
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
            if (argc == 2) {
                std::cout << crl_cmd;
                return 0;
            }
            return handle_crl(crl_cmd);
        case Command::BUNDLE:
            return handle_bundle(bundle_cmd);
        case Command::PARSE:
            return handle_parse(parse_cmd);
        case Command::UNKNOWN:
        default:
            return 1;
    }
}
