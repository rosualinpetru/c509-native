#ifndef __C509__CERTIFICATE_H
#define __C509__CERTIFICATE_H

#include "tbscert.hpp"
#include "sig.hpp"
#include "util.hpp"

namespace C509
{
    struct Certificate
    {
        const TBSCertificate tbsCertificate;
        const IssuerSignatureValue issuerSignatureValue;
    };
}

#endif // __C509__CERTIFICATE_H