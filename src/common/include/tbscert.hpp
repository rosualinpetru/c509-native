#ifndef __C509__TBSCERTIFICATE_H
#define __C509__TBSCERTIFICATE_H

#include <cstddef>
#include <cstdint>
#include <optional>

#include "csn.hpp"
#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "util.hpp"

namespace C509
{
    struct TBSCertificate
    {
        const uint8_t c509CertificateType;
        const CertificateSerialNumber certificateSerialNumber;
        const AlgorithmIdentifier issuerSignatureAlgorithm;
        const std::optional<Name> issuer;
        const uint32_t validityNotBefore;
        const std::optional<uint32_t> validityNotAfter;
        const Name subject;
        const AlgorithmIdentifier subjectPublicKeyAlgorithm;
        const SubjectPublicKey subjectPublicKey;
        // const Extensions extensions;
    };
}

#endif // __C509__TBSCERTIFICATE_H