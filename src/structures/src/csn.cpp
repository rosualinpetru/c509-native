#include "c509_types/csn.hpp"

std::string C509::CertificateSerialNumber::to_string() const {
    return bytes.to_hex_string();
}
