#include "c509_types/ext.hpp"

#include <sstream>

std::string C509::Extension::to_string() const {
    std::ostringstream oss;
    oss << "Id: " << oidExtension.extension_id.to_string()
            << ", Critical: " << (oidExtension.critical ? "true" : "false")
            << ", Value: " << oidExtension.extension_value.to_hex_string();
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
