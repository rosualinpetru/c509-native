#include <string>


#include "c509_core/c509.hpp"

namespace C509 {
    bool map_algid_to_oid(const std::string &algorithm, AlgorithmIdentifier &identifier) {
        const auto it = valid_algorithms.find(algorithm);
        if (it == valid_algorithms.end()) {
            return false;
        }

        identifier.type = AlgorithmIdentifier::Type::OID;
        identifier.oid_algorithm_identifier.algorithm_identifier.subids.copy(it->second.data(), it->second.size());
        identifier.oid_algorithm_identifier.parameters.reset();
        return true;
    }
}
