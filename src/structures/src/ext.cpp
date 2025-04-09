#include "c509_types/ext.hpp"

#include <sstream>

std::string C509::Extension::to_string() const {
    std::ostringstream oss;
    oss << "Id: " << oid_extension.extension_id.to_string()
            << ", Critical: " << (oid_extension.critical ? "true" : "false")
            << ", Value: " << oid_extension.extension_value.to_hex_string();
    return oss.str();
}


std::string C509::Extensions::to_string() const {
    std::ostringstream oss;
    if (type == Type::MixedKeyUsage) {
        oss << mixed_key_usage;
    } else {
        oss << "{";
        for (size_t i = 0; i < extensions.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << "(" << extensions[i].to_string() << ")";
        }
        oss << "}";
    }
    return oss.str();
}

std::string C509::KeyUsage::to_string() const {
    return std::to_string(value);
}

std::string C509::BasicConstraints::to_string() const {
    return std::to_string(value);
}

std::string C509::SubjectKeyIdentifier::to_string() const {
    return value.to_hex_string();
}
