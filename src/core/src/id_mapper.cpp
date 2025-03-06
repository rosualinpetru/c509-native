#include <string>

#include "c509_core/c509.hpp"

bool map_alg_to_id(const std::string &algorithm, C509::AlgorithmIdentifier &identifier) {
    const auto it = supported_cert_algorithms.find(algorithm);
    if (it == supported_cert_algorithms.end())
        return false;

    identifier.type = C509::AlgorithmIdentifier::Type::OID;
    identifier.oid_algorithm_identifier.algorithm_identifier.subids.copy(it->second.data(), it->second.size());
    identifier.oid_algorithm_identifier.parameters.reset();
    return true;
}

bool map_id_to_alg(std::string &algorithm, const C509::AlgorithmIdentifier &identifier) {
    const C509::OID *alg_oid = nullptr;
    // Extract the public key
    switch (identifier.type) {
        case C509::AlgorithmIdentifier::Type::OID:
            alg_oid = &identifier.oid_algorithm_identifier.algorithm_identifier;
            break;
        default:
            return false;
    }

    algorithm = "";
    for (const auto &[name, oid]: supported_cert_algorithms) {
        if (*alg_oid == C509::OID(oid.data(), oid.size())) {
            algorithm = name;
            break;
        }
    }

    if (algorithm.empty()) {
        return false;
    }

    return true;
}
