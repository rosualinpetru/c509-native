#ifndef __C509_C509_CODEC_H
#define __C509_C509_CODEC_H

#include "cbor_codec.hpp"
#include "c509_types.hpp"

using namespace C509;

#define DECLARE_C509_CBOR_CODEC(Type)                      \
    template <>                                            \
    struct C509::CBORCodec<Type>                           \
    {                                                      \
        static inline CBORState encode(const Type &input); \
        static inline Type decode(const CBORState &input); \
    };

DECLARE_C509_CBOR_CODEC(Certificate)
DECLARE_C509_CBOR_CODEC(TBSCertificate)
DECLARE_C509_CBOR_CODEC(CertificateSerialNumber)
DECLARE_C509_CBOR_CODEC(AlgorithmIdentifier)
DECLARE_C509_CBOR_CODEC(Name)
DECLARE_C509_CBOR_CODEC(Attribute)
DECLARE_C509_CBOR_CODEC(SubjectPublicKey)
DECLARE_C509_CBOR_CODEC(IssuerSignatureValue)

#endif // __C509_C509_CODEC_H