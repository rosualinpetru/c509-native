#include "c509_types/oid.hpp"

#include <sstream>

C509::OID::OID() = default;

C509::OID::OID(const uint32_t *data, const size_t size) {
    subids.copy(data, size);
}

bool C509::OID::operator==(const OID &other) const {
    if (subids.size() != other.subids.size()) return false;
    for (size_t i = 0; i < subids.size(); ++i)
        if (subids[i] != other.subids[i]) return false;
    return true;
}

std::string C509::OID::to_string() const {
    if (subids.empty()) return "<empty>";

    std::ostringstream oss;
    for (size_t i = 0; i < subids.size(); ++i) {
        if (i > 0) oss << ".";
        oss << subids[i];
    }
    return oss.str();
}
