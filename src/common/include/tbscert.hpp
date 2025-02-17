#ifndef __C509_TBSCERTIFICATE_H
#define __C509_TBSCERTIFICATE_H

#include <cstddef>
#include <cstdint>

#include "csn.hpp"
#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "structures.hpp"

namespace C509
{
    struct TBSCertificate
    {
        uint8_t c509CertificateType;
        CertificateSerialNumber certificateSerialNumber;
        AlgorithmIdentifier issuerSignatureAlgorithm;
        optional<Name> issuer;
        uint32_t validityNotBefore;
        optional<uint32_t> validityNotAfter;
        Name subject;
        AlgorithmIdentifier subjectPublicKeyAlgorithm;
        SubjectPublicKey subjectPublicKey;
        // Extensions extensions;
    };
}

#endif // __C509_TBSCERTIFICATE_H