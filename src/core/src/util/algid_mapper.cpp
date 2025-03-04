#include <string>
#include <unordered_map>
#include <vector>

#include "c509_core/algid_mapper.hpp"

namespace C509 {
    bool algid_mapper(const std::string &algorithm, AlgorithmIdentifier &identifier) {
        static const std::unordered_map<std::string, std::vector<uint32_t> > alg_to_oid = {
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

        const auto it = alg_to_oid.find(algorithm);
        if (it == alg_to_oid.end()) {
            return false;
        }

        identifier.type = AlgorithmIdentifier::Type::OID;
        identifier.oidAlgorithmIdentifier.algorithmIdentifier.subids.copy(it->second.data(), it->second.size());
        identifier.oidAlgorithmIdentifier.parameters.reset();
        return true;
    }
}
