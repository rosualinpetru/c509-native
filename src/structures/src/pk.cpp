#include "c509_types/pk.hpp"

#include <sstream>

std::string C509::PublicKey::to_string() const {
    std::ostringstream oss;
    oss << "PublicKey[" << bytes.size() << "]: ";
    if (bytes.size() > 6) {
        oss << bytes.to_hex_string(0, 3) << " ... " << bytes.to_hex_string(bytes.size() - 3, 3);
    } else {
        oss << bytes.to_hex_string(0, bytes.size());
    }
    return oss.str();
}
