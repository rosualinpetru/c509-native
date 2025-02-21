#ifndef __C509_TBSCERTIFICATE_H
#define __C509_TBSCERTIFICATE_H

#include "structures.hpp"

#include "csn.hpp"
#include "algid.hpp"
#include "name.hpp"
#include "time.hpp"
#include "pk.hpp"
#include "ext.hpp"

namespace C509
{
    struct TBSCertificate
    {
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
}

#endif // __C509_TBSCERTIFICATE_H