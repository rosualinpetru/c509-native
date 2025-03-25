#include "c509_types/attr.hpp"

#include <sstream>

std::string C509::Attribute::to_string() const {
    std::ostringstream oss;
    if (type == Type::Int) {
        oss << static_cast<int>(attribute_type.integer)
                << " -> " << "\"" << attribute_value.to_utf8_string() << "\"";
    } else if (type == Type::OID) {
        oss << "" << attribute_type.oid.to_string()
                << " -> " << attribute_value.to_hex_string();
    }
    return oss.str();
}
