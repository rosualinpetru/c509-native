#ifndef C509_CSR_H
#define C509_CSR_H

#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "sig.hpp"
#include "ext.hpp"

namespace C509::CSR {
    struct TBSCertificateRequest {
        uint8_t c509CertificateRequestType;
        AlgorithmIdentifier subjectSignatureAlgorithm;
        Name subject;
        AlgorithmIdentifier subjectPublicKeyAlgorithm;
        SubjectPublicKey subjectPublicKey;
        Extensions extensionsRequest;
    };

    struct C509CertificateRequest {
        TBSCertificateRequest tbsCertificateRequest;
        SignatureValue subjectSignatureValue;
    };
}

#endif // C509_CSR_H
