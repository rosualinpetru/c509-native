#ifndef C509_C509_CODEC_H
#define C509_C509_CODEC_H

#include "c509_types/types.hpp"

#define DECLARE_CODEC(Type)                                                                       \
    int cbor_encode(uint8_t *payload, size_t payload_len, const Type *input, size_t *payload_len_out); \
    int cbor_decode(const uint8_t *payload, size_t payload_len, Type *result, size_t *payload_len_out);

namespace C509 {
    DECLARE_CODEC(TBSCertificate)
    DECLARE_CODEC(C509Certificate)
    DECLARE_CODEC(C509PrivateKey)
    DECLARE_CODEC(C509PEM)
    DECLARE_CODEC(COSE_C509)

    namespace CSR {
        DECLARE_CODEC(TBSCertificateRequest)
        DECLARE_CODEC(C509CertificateRequest)
    }

    namespace CRL {
        DECLARE_CODEC(C509CertificateRevocationList)
    }
}

#endif // C509_C509_CODEC_H
