#ifndef C509_CSR_H
#define C509_CSR_H

#include "structures.hpp"

#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "sig.hpp"
#include "ext.hpp"

#define MAX_CHALLENGE_PASSWORD_LEN 64 // TODO

namespace C509::CSR {
    struct ChallengePassword {
        enum class Type {
            BSTR,
            TSTR
        } type;

        bounded_array<uint8_t, MAX_CHALLENGE_PASSWORD_LEN> bytes;
    };

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
        optional<ChallengePassword> challengePassword;
    };
}

#endif // C509_CSR_H
