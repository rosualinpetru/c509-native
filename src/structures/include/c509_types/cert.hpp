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
        uint8_t c509_certificate_type{};
        CertificateSerialNumber certificate_serial_number;
        AlgorithmIdentifier issuer_signature_algorithm;
        optional<Name> issuer;
        Time validity_not_before{};
        optional<Time> validity_not_after;
        Name subject;
        AlgorithmIdentifier subject_public_key_algorithm;
        PublicKey subject_public_key;
        Extensions extensions;

        std::string to_string() const;
    };

    struct C509Certificate {
        TBSCertificate tbs_certificate;
        SignatureValue signature_value;

        std::string to_string() const;
    };
}

#endif // C509_C509CERTIFICATE_H
