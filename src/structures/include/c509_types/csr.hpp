#ifndef C509_CSR_H
#define C509_CSR_H

#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "sig.hpp"
#include "ext.hpp"

namespace C509::CSR {
    struct TBSCertificateRequest {
        uint8_t c509_certificate_request_type{};
        AlgorithmIdentifier subject_signature_algorithm;
        Name subject;
        AlgorithmIdentifier subject_public_key_algorithm;
        PublicKey subject_public_key;
        Extensions extensions_request;

        std::string to_string() const;
    };

    struct C509CertificateRequest {
        TBSCertificateRequest tbs_certificate_request;
        SignatureValue subject_signature_value;

        std::string to_string() const;
    };
}

#endif // C509_CSR_H
