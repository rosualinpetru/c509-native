#ifndef C509_CLI_HPP
#define C509_CLI_HPP

int main(int argc, char *argv[]);

int handle_genpkey(const argparse::ArgumentParser &genpkey_cmd);
int handle_req(const argparse::ArgumentParser &req_cmd);

#endif // C509_CLI_HPP