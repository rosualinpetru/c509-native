#ifndef CBOR_CODEC_INTERNAL_H
#define CBOR_CODEC_INTERNAL_H

#include <zcbor_encode.h>
#include <zcbor_decode.h>
#include <zcbor_print.h>

#include "c509_codec/codec.hpp"
#include "codec_errors.hpp"

#define DECLARE_CBOR_CODEC_TEMPLATE() \
    template <typename T>             \
    struct CBORCodec;

#define CBOR_CODEC_MODE_NORMAL /* Empty */
#define CBOR_CODEC_MODE_UNWRAPPED _unwrapped

#define APPEND_SUFFIX(x, y) x##y

#define DECLARE_CBOR_CODEC_SPECIALIZATION(Type, Mode)                                      \
    template <>                                                                            \
    struct CBORCodec<Type>                                                                 \
    {                                                                                      \
        static bool APPEND_SUFFIX(encode, Mode)(zcbor_state_t * state, const Type &input); \
        static bool APPEND_SUFFIX(decode, Mode)(zcbor_state_t * state, Type &output);      \
    };

#define DECLARE_CBOR_CODEC(Type) DECLARE_CBOR_CODEC_SPECIALIZATION(Type, CBOR_CODEC_MODE_NORMAL)
#define DECLARE_CBOR_CODEC_UNWRAPPED(Type) DECLARE_CBOR_CODEC_SPECIALIZATION(Type, CBOR_CODEC_MODE_UNWRAPPED)

namespace C509 {
    DECLARE_CBOR_CODEC_TEMPLATE()

    DECLARE_CBOR_CODEC(C509PrivateKey)

    DECLARE_CBOR_CODEC(C509Certificate)

    DECLARE_CBOR_CODEC(TBSCertificate)

    DECLARE_CBOR_CODEC(CertificateSerialNumber)

    DECLARE_CBOR_CODEC(AlgorithmIdentifier)

    DECLARE_CBOR_CODEC(Name)

    DECLARE_CBOR_CODEC(Attribute)

    DECLARE_CBOR_CODEC(SubjectPublicKey)

    DECLARE_CBOR_CODEC(SignatureValue)

    DECLARE_CBOR_CODEC_UNWRAPPED(OID)

    DECLARE_CBOR_CODEC_UNWRAPPED(Time)

    DECLARE_CBOR_CODEC(Extensions)

    DECLARE_CBOR_CODEC(Extension)

    namespace CSR {
        DECLARE_CBOR_CODEC_TEMPLATE()

        DECLARE_CBOR_CODEC(ChallengePassword)

        DECLARE_CBOR_CODEC(TBSCertificateRequest)

        DECLARE_CBOR_CODEC(C509CertificateRequest)
    }

    namespace CRL {
        DECLARE_CBOR_CODEC_TEMPLATE()

        DECLARE_CBOR_CODEC(C509CertificateRevocationList)

        DECLARE_CBOR_CODEC(TBSCertificateRevocationList)

        DECLARE_CBOR_CODEC(RevokedCertificate)
    }
}

#endif // CBOR_CODEC_INTERNAL_H
