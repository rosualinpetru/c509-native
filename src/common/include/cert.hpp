#ifndef __C509_C509CERTIFICATE_H
#define __C509_C509CERTIFICATE_H

#include "tbscert.hpp"
#include "sig.hpp"

namespace C509
{
    struct C509Certificate
    {
        TBSCertificate tbsCertificate;
        IssuerSignatureValue issuerSignatureValue;
    };
}

#endif // __C509_C509CERTIFICATE_H