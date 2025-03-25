#include "c509_types/cert.hpp"

#include <sstream>

std::string C509::TBSCertificate::to_string() const {
    std::ostringstream oss;
    oss << "TBSCertificate:\n"
            << "  Type: " << static_cast<int>(c509_certificate_type) << "\n"
            << "  Serial Number: " << certificate_serial_number.to_string() << "\n"
            << "  Issuer Signature Algorithm: " << issuer_signature_algorithm.to_string() << "\n";

    if (issuer.has()) {
        oss << "  Issuer: " << issuer.get().to_string() << "\n";
    } else {
        oss << "  Issuer: null\n";
    }

    oss << "  Validity Not Before: " << validity_not_before.to_string() << "\n";

    if (validity_not_after.has()) {
        oss << "  Validity Not After: " << validity_not_after.get().to_string() << "\n";
    } else {
        oss << "  Validity Not After: null\n";
    }

    oss << "  Subject: " << subject.to_string() << "\n"
            << "  Subject Public Key Algorithm: " << subject_public_key_algorithm.to_string() << "\n"
            << "  Subject Public Key: " << subject_public_key.to_string() << "\n"
            << "  Extensions: " << extensions.to_string();

    return oss.str();
}

std::string  C509::C509Certificate::to_string() const {
    std::ostringstream oss;
    oss << "C509Certificate:\n"
            << tbs_certificate.to_string() << "\n"
            << "Signature: " << signature_value.to_string();
    return oss.str();
}
