#ifndef C509_CRL_H
#define C509_CRL_H

#include "structures.hpp"

#include "csn.hpp"
#include "time.hpp"
#include "ext.hpp"
#include "algid.hpp"
#include "name.hpp"
#include "sig.hpp"

#define MAX_REVOKED_CERTIFICATES 32 // TODO

namespace C509::CRL {
    struct RevokedCertificate {
        CertificateSerialNumber user_certificate;
        Time revocation_date;
        Extensions crl_entry_extensions;
    };

    struct TBSCertificateRevocationList {
        uint8_t c509_certificate_revocation_list_type{};
        Name issuer;
        Time this_update{};
        Time next_update{};
        bounded_array<RevokedCertificate, MAX_REVOKED_CERTIFICATES> revoked_certificates;
        Extensions crl_extensions;
        AlgorithmIdentifier issuer_signature_algorithm;
    };

    struct C509CertificateRevocationList {
        TBSCertificateRevocationList tbs_certificate_revocation_list;
        SignatureValue issuer_signature_value;
    };
}

#endif // C509_CRL_H
