#ifndef __C509_CBOR_CODEC_H
#define __C509_CBOR_CODEC_H

#include <zcbor_encode.h>
#include <zcbor_decode.h>
#include <zcbor_print.h>

#include "c509_codec.hpp"
#include "c509_codec_errors.hpp"

#define CBOR_CODEC_MODE_NORMAL /* Empty */
#define CBOR_CODEC_MODE_UNWRAPPED _unwrapped

#define APPED_SUFFIX(x, y) x##y

#define DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type, Mode)                 \
    template <>                                                            \
    struct CBORCodec<Type>                                                 \
    {                                                                      \
        static bool APPED_SUFFIX(encode, Mode)(zcbor_state_t *state, const Type &input); \
        static bool APPED_SUFFIX(decode, Mode)(zcbor_state_t *state, Type &output);      \
    };

#define DECLARE_C509_CBOR_CODEC(Type) DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type, CBOR_CODEC_MODE_NORMAL)
#define DECLARE_C509_CBOR_CODEC_UNWRAPPED(Type) DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type, CBOR_CODEC_MODE_UNWRAPPED)

namespace C509
{
    template <typename T>
    struct CBORCodec;

    DECLARE_C509_CBOR_CODEC_UNWRAPPED(C509Certificate)
    DECLARE_C509_CBOR_CODEC_UNWRAPPED(OID)
    DECLARE_C509_CBOR_CODEC_UNWRAPPED(Time)

    DECLARE_C509_CBOR_CODEC(TBSCertificate)
    DECLARE_C509_CBOR_CODEC(CertificateSerialNumber)
    DECLARE_C509_CBOR_CODEC(AlgorithmIdentifier)
    DECLARE_C509_CBOR_CODEC(Name)
    DECLARE_C509_CBOR_CODEC(Attribute)
    DECLARE_C509_CBOR_CODEC(SubjectPublicKey)
    DECLARE_C509_CBOR_CODEC(IssuerSignatureValue)
}

#define log_result(state, result, func)                                                    \
    do                                                                                     \
    {                                                                                      \
        if (!result)                                                                       \
        {                                                                                  \
            zcbor_trace_file(state);                                                       \
            zcbor_log("%s error: %s\r\n", func, zcbor_error_str(zcbor_peek_error(state))); \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            zcbor_log("%s success\r\n", func);                                             \
        }                                                                                  \
    } while (0)

#define fail(message, error) \
    {                        \
        zcbor_log(message);  \
        ZCBOR_ERR(error);    \
    }

#endif // __C509_CBOR_CODEC_H