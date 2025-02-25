#ifndef __C509_CSR_H
#define __C509_CSR_H

#include "structures.hpp"

#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "ext.hpp"

// WARNING
#define MAX_CHALLENGE_PASSWORD_LEN 20

namespace C509
{
    namespace CSR
    {
        struct TBSCertificateRequest
        {
            uint8_t c509CertificateRequestType;
            AlgorithmIdentifier subjectSignatureAlgorithm;
            Name subject;
            AlgorithmIdentifier subjectPublicKeyAlgorithm;
            SubjectPublicKey subjectPublicKey;
            Extensions extensionsRequest;
        };

        struct C509CertificateRequest
        {
            TBSCertificateRequest tbsCertificateRequest;
            SignatureValue subjectSignatureValue;
            optional<bounded_array<uint8_t, MAX_CHALLENGE_PASSWORD_LEN>> challengePassword;
        };
    }
}

#endif // __C509_CSR_H