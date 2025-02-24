#ifndef __C509_CBOR_CODEC_H
#define __C509_CBOR_CODEC_H

#include <zcbor_encode.h>
#include <zcbor_decode.h>
#include <zcbor_print.h>

#include "c509_codec.hpp"
#include "c509_codec_errors.hpp"

#define CBOR_CODEC_MODE_NORMAL /* Empty */
#define CBOR_CODEC_MODE_UNWRAPPED _unwrapped

#define APPEND_SUFFIX(x, y) x##y

#define DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type, Mode)                                 \
    template <>                                                                            \
    struct CBORCodec<Type>                                                                 \
    {                                                                                      \
        static bool APPEND_SUFFIX(encode, Mode)(zcbor_state_t * state, const Type &input); \
        static bool APPEND_SUFFIX(decode, Mode)(zcbor_state_t * state, Type &output);      \
    };

#define DECLARE_C509_CBOR_CODEC(Type) DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type, CBOR_CODEC_MODE_NORMAL)
#define DECLARE_C509_CBOR_CODEC_UNWRAPPED(Type) DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type, CBOR_CODEC_MODE_UNWRAPPED)

#define DECLARE_C509_CBOR_CODEC_SPECIALIZATION_ALGID_DEPENDANT(Type)                                           \
    template <>                                                                                                \
    struct CBORCodec<Type>                                                                                     \
    {                                                                                                          \
        static bool encode(zcbor_state_t * state, const Type &input, AlgorithmIdentifier algId); \
        static bool decode(zcbor_state_t * state, Type &output, AlgorithmIdentifier algId);      \
    };

namespace C509
{
    template <typename T>
    struct CBORCodec;

    DECLARE_C509_CBOR_CODEC(C509Certificate)
    DECLARE_C509_CBOR_CODEC(TBSCertificate)
    DECLARE_C509_CBOR_CODEC(CertificateSerialNumber)
    DECLARE_C509_CBOR_CODEC(AlgorithmIdentifier)
    DECLARE_C509_CBOR_CODEC(Name)
    DECLARE_C509_CBOR_CODEC(Attribute)

    DECLARE_C509_CBOR_CODEC(Extensions)
    DECLARE_C509_CBOR_CODEC(Extension)

    DECLARE_C509_CBOR_CODEC_UNWRAPPED(OID)
    DECLARE_C509_CBOR_CODEC_UNWRAPPED(Time)

    DECLARE_C509_CBOR_CODEC_SPECIALIZATION_ALGID_DEPENDANT(SubjectPublicKey)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION_ALGID_DEPENDANT(IssuerSignatureValue)
}

#endif // __C509_CBOR_CODEC_H