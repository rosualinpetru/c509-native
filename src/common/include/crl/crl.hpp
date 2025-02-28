#ifndef __C509_CRL_H
#define __C509_CRL_H

#include "structures.hpp"

#include "csn.hpp"
#include "time.hpp"
#include "ext.hpp"
#include "algid.hpp"
#include "name.hpp"
#include "pk.hpp"
#include "sig.hpp"

// TODO
#define MAX_REVOKED_CERTIFICATES 4096

namespace C509
{
    namespace CRL
    {
        struct RevokedCertificate
        {
            CertificateSerialNumber userCertificate;
            Time revocationDate;
            Extensions crlEntryExtensions;
        };

        struct TBSCertificateRevocationList
        {
            uint8_t c509CertificateRevocationListType;
            Name issuer;
            Time thisUpdate;
            Time nextUpdate;
            bounded_array<RevokedCertificate, MAX_REVOKED_CERTIFICATES> revokedCertificates;
            Extensions crlExtensions;
            AlgorithmIdentifier issuerSignatureAlgorithm;
        };

        struct C509CertificateRevocationList
        {
            TBSCertificateRevocationList tbsCertificateRevocationList;
            SignatureValue issuerSignatureValue;
        };
    }
}

#endif // __C509_CRL_H