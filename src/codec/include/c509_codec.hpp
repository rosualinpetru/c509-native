#ifndef __C509_C509_CODEC_H
#define __C509_C509_CODEC_H

#include "cert/cert.hpp"
#include "csr/csr.hpp"
#include "crl/crl.hpp"

#define DECLARE_CODEC(Type)                                                                       \
    int encode(uint8_t *payload, size_t payload_len, const Type *input, size_t *payload_len_out); \
    int decode(const uint8_t *payload, size_t payload_len, Type *result, size_t *payload_len_out);

namespace C509
{
    DECLARE_CODEC(C509Certificate)

    namespace CSR
    {
        DECLARE_CODEC(C509CertificateRequest)
    }

    namespace CRL
    {
        DECLARE_CODEC(C509CertificateRevocationList)
    }

}

#endif // __C509_C509_CODEC_H