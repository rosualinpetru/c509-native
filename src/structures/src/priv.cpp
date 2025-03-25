#include "c509_types/priv.hpp"

#include <sstream>

std::string C509::PrivateKey::to_string() const {
    std::ostringstream oss;
    oss << "PrivateKey[" << bytes.size() << "]: ";
    if (bytes.size() > 6) {
        oss << bytes.to_hex_string(0, 3) << " ... " << bytes.to_hex_string(bytes.size() - 3, 3);
    } else {
        oss << bytes.to_hex_string();
    }
    return oss.str();
}

std::string C509::PrivateKeyInfo::to_string() const {
    std::ostringstream oss;
    oss << "PrivateKeyInfo:\n"
        << "    " << private_key.to_string() << "\n"
        << "    " << public_key.to_string();
    return oss.str();
}

std::string C509::C509PrivateKey::to_string() const {
    std::ostringstream oss;
    oss << "C509PrivateKey:\n"
        << "  Subject Private Key Algorithm: " << subject_private_key_algorithm.to_string() << "\n"
        << "  " << subject_private_key_info.to_string();
    return oss.str();
}

std::string C509::C509PEM::to_string() const {
    std::ostringstream oss;
    oss << "C509PEM:\n"
        << private_key.to_string() << "\n";
    
    if (cose_c509.has()) {
        oss << "  COSE_C509: " << cose_c509.get().to_string();
    } else {
        oss << "  COSE_C509: <none>";
    }

    return oss.str();
}