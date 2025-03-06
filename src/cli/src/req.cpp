#include <iostream>
#include <fstream>
#include <argparse/argparse.hpp>

#include "file/file_util.hpp"

#include "c509_core/c509.hpp"

#include "c509_cli/cli.hpp"

#define MAX_BUFFER_SIZE 16384

std::string get_interactive_subject();

bool parse_subject(const std::string &subject, std::map<uint32_t, std::string> &parsed_attributes);

bool parse_extensions(const std::vector<std::string> &extensions,
                      std::map<std::vector<uint32_t>, std::tuple<bool, std::string> > &parsed_extensions);

int handle_req(const argparse::ArgumentParser &req_cmd) {
    // Parse arguments
    const auto in = req_cmd.present<std::string>("-in");
    const auto verify = req_cmd.get<bool>("-verify");
    auto is_new = req_cmd.get<bool>("-new");
    auto c509 = req_cmd.get<bool>("-c509");
    const auto ca_cert = req_cmd.present<std::string>("-CA");
    const auto ca_key = req_cmd.present<std::string>("-CAkey");
    const auto subj = req_cmd.present<std::string>("-subj");
    const auto days = req_cmd.get<int>("-days");
    const auto serial_number = req_cmd.present<int>("-set_serial");
    const auto key = req_cmd.present<std::string>("-key");
    const auto out = req_cmd.present<std::string>("-out");
    const auto batch = req_cmd.get<bool>("-batch");
    const auto addext = req_cmd.present<std::vector<std::string> >("-addext");

    // Flags implications
    c509 = ca_cert.has_value() ? true : c509;
    is_new = c509 && !in.has_value() ? true : is_new; // new is true if x509 is true and no -in is given

    uint8_t private_key[MAX_BUFFER_SIZE] = {};
    size_t private_key_size = sizeof(private_key);

    uint8_t csr_buffer[MAX_BUFFER_SIZE] = {};
    size_t csr_buffer_size = sizeof(csr_buffer);

    // --- Handle New Request (CSR or Self-Signed Certificate) ---
    if (is_new) {
        if (!key) {
            std::cerr << "Error: -key is required when generating a new CSR or certificate.\n";
            return 1;
        }

        if (!out.has_value()) {
            std::cerr << "Error: -out is required.\n";
            return 1;
        }

        std::string subject_raw;

        // Require subject data
        if (batch) {
            if (!subj.has_value()) {
                std::cerr << "Error: -subj is required in batch mode.\n";
                return 1;
            }
            subject_raw = subj.value();
        } else {
            subject_raw = subj.has_value() ? subj.value() : get_interactive_subject();
        }

        auto extensions_raw = addext.has_value() ? *addext : std::vector<std::string>();

        read_binary_file(key.value(), private_key, private_key_size);

        std::map<uint32_t, std::string> subject;
        std::map<std::vector<uint32_t>, std::tuple<bool, std::string> > extensions;
        if (!parse_subject(subject_raw, subject) || !parse_extensions(extensions_raw, extensions))
            return 1;

        gen_csr(private_key, private_key_size, subject, extensions, csr_buffer, csr_buffer_size);
        if (!c509)
            write_binary_file(out.value(), csr_buffer, csr_buffer_size);
    } else {
        // --- Process Existing CSR (Verification or Other Operations) ---
        if (in.has_value()) {
            read_binary_file(in.value(), csr_buffer, csr_buffer_size);

            if (verify) {
                if (!verify_csr(csr_buffer, csr_buffer_size)) {
                    std::cerr << "Error: CSR verification failed.\n";
                    return 1;
                }
            }

            if (subj.has_value() || addext.has_value()) {
                std::cerr << "Error: -subj and -addext are not supported when reading a CSR from a file.\n";
                return 1;
            }
        } else {
            std::cerr << "Error: No input provided. Use either the -new or -in flag.\n";
            return 1;
        }
    }

    // CSR present; private key is present only if new

    if (c509) {
        if (!out.has_value()) {
            std::cerr << "Error: -out is required.\n";
            return 1;
        }

        // --- Get days and serial ---
        if (!serial_number.has_value()) {
            std::cerr << "Error: -set_serial is required when generating a certificate.\n";
            return 1;
        }

        uint8_t cert_out[MAX_BUFFER_SIZE] = {};
        size_t cert_out_size = sizeof(cert_out);

        if (ca_cert.has_value() && ca_key.has_value()) {
            // CA Signed Certificate

            uint8_t ca_cert_buffer[MAX_BUFFER_SIZE] = {};
            size_t ca_cert_size = sizeof(ca_cert_buffer);

            read_binary_file(ca_key.value(), private_key, private_key_size);

            // if (!sign_csr(csr_buffer, csr_buffer_size, private_key, private_key_size, ca_cert_buffer, ca_cert_size,
            //               days,
            //               serial_number.value(), cert_out, cert_out_size)) {
            //     std::cerr << "Error: CA signing failed.\n";
            //     return 1;
            // }
        } else {
            if (!key) {
                std::cerr << "Error: -key is required when generating a new CSR or certificate.\n";
                return 1;
            }

            read_binary_file(key.value(), private_key, private_key_size);

            if (!self_sign_csr(csr_buffer, csr_buffer_size, private_key, private_key_size, days,
                               serial_number.value(), cert_out, cert_out_size)) {
                std::cerr << "Error: Self-signed certificate generation failed.\n";
                return 1;
            }
        }

        write_binary_file(out.value(), cert_out, cert_out_size);
    }

    return 0;
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
            .help("Key for signing, and to include unless -in given");

    // Output
    req_cmd.add_argument("-out")
            .help("Output file");

    req_cmd.add_argument("-batch")
            .default_value(false)
            .implicit_value(true)
            .help("Do not ask anything during request generation");
}

std::string get_input(const std::string &field, const std::string &default_value) {
    std::cout << field << " [" << default_value << "]: ";
    std::string value;
    std::getline(std::cin, value);
    return value.empty() ? default_value : value;
}

std::string get_interactive_subject() {
    std::cout << "Enter subject information (leave blank for defaults):\n";
    const std::string country = get_input("Country", "US");
    const std::string state = get_input("State", "California");
    const std::string locality = get_input("Locality", "San Francisco");
    const std::string organization = get_input("Organization", "Example Inc.");
    const std::string orgUnit = get_input("Organizational Unit", "Engineering");
    const std::string commonName = get_input("Common Name", "example.com");
    const std::string email = get_input("Email Address", "admin@example.com");

    return "/C=" + country + "/ST=" + state + "/L=" + locality + "/O=" + organization +
           "/OU=" + orgUnit + "/CN=" + commonName + "/emailAddress=" + email;
}

std::string to_lowercase(const std::string &str) {
    std::string lower = str;
    std::ranges::transform(lower, lower.begin(),
                           [](const unsigned char c) { return std::tolower(c); });
    return lower;
}

bool parse_subject(const std::string &subject, std::map<uint32_t, std::string> &parsed_attributes) {
    std::istringstream stream(subject);
    std::string token;

    while (std::getline(stream, token, '/')) {
        if (token.empty()) continue;

        const auto pos = token.find('=');
        if (pos == std::string::npos) {
            std::cerr << "Error: Invalid attribute format: " << token << std::endl;
            return false;
        }

        std::string identifier = token.substr(0, pos);
        std::string value = token.substr(pos + 1);

        std::string lower_identifier = to_lowercase(identifier);

        auto it = attribute_registry.find(lower_identifier);
        if (it == attribute_registry.end()) {
            std::cerr << "Error: Unsupported attribute identifier: " << identifier << std::endl;
            return false;
        }

        int index = it->second;
        parsed_attributes[index] = value;
    }

    return true;
}

bool parse_extensions(const std::vector<std::string> &extensions,
                      std::map<std::vector<uint32_t>, std::tuple<bool, std::string> > &parsed_extensions) {
    for (const auto &ext: extensions) {
        size_t eq_pos = ext.find('=');
        if (eq_pos == std::string::npos) {
            return false;
        }

        std::string identifier = ext.substr(0, eq_pos);
        std::string value_part = ext.substr(eq_pos + 1);

        // Check if the identifier exists in the supported extensions map
        auto it = supported_cert_extensions.find(identifier);
        if (it == supported_cert_extensions.end()) {
            std::cerr << "Error: Unsupported extension: " << identifier << std::endl;
            return false;
        }

        // Parse critical flag and value
        bool critical = false;
        std::string value;

        if (value_part.rfind("critical, ", 0) == 0) {
            critical = true;
            value = value_part.substr(10);
        } else {
            value = value_part;
        }

        if (value.empty()) {
            std::cerr << "Error: Empty extension value: " << identifier << std::endl;
            return false;
        }

        parsed_extensions[it->second] = std::make_tuple(critical, value);
    }

    return true;
}
