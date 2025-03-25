#include "c509_types/crl.hpp"

#include <sstream>

std::string C509::CRL::RevokedCertificate::to_string() const {
    std::ostringstream oss;
    oss << "RevokedCertificate:\n"
            << "  Serial Number: " << user_certificate.to_string() << "\n"
            << "  Revocation Date: " << revocation_date.to_string() << "\n"
            << "  CRL Entry Extensions: " << crl_entry_extensions.to_string();
    return oss.str();
}

std::string C509::CRL::TBSCertificateRevocationList::to_string() const {
    std::ostringstream oss;
    oss << "TBSCertificateRevocationList:\n"
            << "  Type: " << static_cast<int>(c509_certificate_revocation_list_type) << "\n"
            << "  Issuer: " << issuer.to_string() << "\n"
            << "  This Update: " << this_update.to_string() << "\n"
            << "  Next Update: " << next_update.to_string() << "\n"
            << "  Revoked Certificates: ";

    if (revoked_certificates.empty()) {
        oss << "<none>";
    } else {
        oss << "{";
        for (size_t i = 0; i < revoked_certificates.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << revoked_certificates[i].to_string();
        }
        oss << "}";
    }

    oss << "\n  CRL Extensions: " << crl_extensions.to_string() << "\n"
            << "  Issuer Signature Algorithm: " << issuer_signature_algorithm.to_string();
    return oss.str();
}

std::string C509::CRL::C509CertificateRevocationList::to_string() const {
    std::ostringstream oss;
    oss << "C509CertificateRevocationList:\n"
            << tbs_certificate_revocation_list.to_string() << "\n"
            << "  Issuer Signature: " << issuer_signature_value.to_string();
    return oss.str();
}
