#ifndef C509_CORE_H
#define C509_CORE_H

#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

#include "c509_types/types.hpp"

namespace C509 {
    static const std::unordered_map<std::string, std::vector<uint32_t> > valid_algorithms = {
        {"mldsa44", {2, 16, 840, 1, 101, 3, 4, 3, 17}},
        {"mldsa65", {2, 16, 840, 1, 101, 3, 4, 3, 18}},
        {"mldsa87", {2, 16, 840, 1, 101, 3, 4, 3, 19}},
        {"mldsa44_ed25519", {2, 16, 840, 1, 114027, 80, 8, 1, 3}},
        {"mldsa44_p256", {2, 16, 840, 1, 114027, 80, 8, 1, 4}},
        {"mldsa65_ed25519", {2, 16, 840, 1, 114027, 80, 8, 1, 10}},
        {"mldsa65_p256", {2, 16, 840, 1, 114027, 80, 8, 1, 8}},
        {"mldsa65_bp256", {2, 16, 840, 1, 114027, 80, 8, 1, 9}},
        {"mldsa87_ed448", {2, 16, 840, 1, 114027, 80, 8, 1, 13}},
        {"mldsa87_p384", {2, 16, 840, 1, 114027, 80, 8, 1, 11}},
        {"mldsa87_bp384", {2, 16, 840, 1, 114027, 80, 8, 1, 12}}
    };

    bool map_algid_to_oid(const std::string &algorithm, AlgorithmIdentifier &identifier);

    bool keygen(const std::string &algorithm, uint8_t *private_key_out, size_t &private_key_out_size);

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

#endif // C509_CORE_H
