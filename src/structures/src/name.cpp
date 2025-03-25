#include "c509_types/name.hpp"

#include <sstream>

std::string C509::Name::to_string() const {
    std::ostringstream oss;
    if (type == Type::Attributes) {
        oss << "{";
        for (size_t i = 0; i < attributes.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << attributes[i].to_string();
        }
        oss << "}";
    } else if (type == Type::Text) {
        oss << "\"" << raw.to_utf8_string() << "\"";
    } else {
        oss << raw.to_hex_string();
    }
    return oss.str();
}
