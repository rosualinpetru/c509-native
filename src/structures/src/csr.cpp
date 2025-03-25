#include "c509_types/csr.hpp"

#include <sstream>

std::string C509::CSR::TBSCertificateRequest::to_string() const {
    std::ostringstream oss;
    oss << "TBSCertificateRequest:\n"
            << "  Type: " << static_cast<int>(c509_certificate_request_type) << "\n"
            << "  Subject Signature Algorithm: " << subject_signature_algorithm.to_string() << "\n"
            << "  Subject: " << subject.to_string() << "\n"
            << "  Subject Public Key Algorithm: " << subject_public_key_algorithm.to_string() << "\n"
            << "  Subject Public Key: " << subject_public_key.to_string() << "\n"
            << "  Extensions Request: " << extensions_request.to_string();
    return oss.str();
}


std::string C509::CSR::C509CertificateRequest::to_string() const {
    std::ostringstream oss;
    oss << "C509CertificateRequest:\n"
            << tbs_certificate_request.to_string() << "\n"
            << "  Subject Signature: " << subject_signature_value.to_string();
    return oss.str();
}
