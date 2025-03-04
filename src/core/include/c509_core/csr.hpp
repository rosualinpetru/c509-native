#ifndef C509_CSR_GEN_H
#define C509_CSR_GEN_H

#include <string>
#include <cstdint>
#include <optional>

namespace C509::CSR {
    bool generate_csr(
        const std::string &algorithm,
        const std::string &country,
        const std::string &state,
        const std::string &locality,
        const std::string &org,
        const std::string &orgUnit,
        const std::string &commonName,
        const std::string &emailAddress,
        const std::optional<std::string> &challengePassword,

        uint8_t *csr_out,
        size_t &csr_out_size,
        uint8_t *private_key_out,
        size_t &private_key_out_size);
}

#endif // C509_CSR_GEN_H
