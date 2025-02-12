#ifndef __C509_CERTIFICATE_H
#define __C509_CERTIFICATE_H

#include "tbscert.hpp"
#include "sig.hpp"

namespace C509
{
    struct Certificate
    {
        TBSCertificate tbsCertificate;
        IssuerSignatureValue issuerSignatureValue;
    };
}

#endif // __C509_CERTIFICATE_H