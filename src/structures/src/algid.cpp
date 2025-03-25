#include "c509_types/algid.hpp"

#include <sstream>

std::string C509::AlgorithmIdentifier::to_string() const {
    std::ostringstream oss;
    if (type == Type::Int) {
        oss << static_cast<int>(int_algorithm_identifier);
    } else if (type == Type::OID) {
        oss << oid_algorithm_identifier.algorithm_identifier.to_string();
        if (oid_algorithm_identifier.parameters.has()) {
            oss << " | " << oid_algorithm_identifier.parameters.get().to_hex_string();
        }
    }
    return oss.str();
}
