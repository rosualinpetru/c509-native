#ifndef C509_C509CERTIFICATE_H
#define C509_C509CERTIFICATE_H

#include <cstdint>

#include "csn.hpp"
#include "algid.hpp"
#include "name.hpp"
#include "time.hpp"
#include "pk.hpp"
#include "sig.hpp"
#include "ext.hpp"

namespace C509 {
    struct TBSCertificate {
        uint8_t c509CertificateType;
        CertificateSerialNumber certificateSerialNumber;
        AlgorithmIdentifier issuerSignatureAlgorithm;
        optional<Name> issuer;
        Time validityNotBefore;
        optional<Time> validityNotAfter;
        Name subject;
        AlgorithmIdentifier subjectPublicKeyAlgorithm;
        SubjectPublicKey subjectPublicKey;
        Extensions extensions;
    };

    struct C509Certificate {
        TBSCertificate tbsCertificate;
        SignatureValue signatureValue;
    };
}

#endif // C509_C509CERTIFICATE_H
