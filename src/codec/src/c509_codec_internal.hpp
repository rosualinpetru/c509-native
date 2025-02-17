#ifndef __C509_CBOR_CODEC_H
#define __C509_CBOR_CODEC_H

#include "c509_codec.hpp"

#include <zcbor_encode.h>
#include <zcbor_decode.h>
#include <zcbor_print.h>

// ERRORS

// CSN
#define C509_ERR_CSN_ENC_INVALID_INPUT 509'000'000

#define C509_ERR_CSN_DEC_BSTR_FAILED 509'000'001
#define C509_ERR_CSN_DEC_EXCEEDED_LENGTH 509'000'002
#define C509_ERR_CSN_DEC_BUFF_COPY 509'000'003

// OID
#define C509_ERR_OID_ENC_INVALID_INPUT 509'001'000

#define C509_ERR_OID_DEC_BSTR_FAILED 509'001'001
#define C509_ERR_OID_DEC_INVALID_LENGTH 509'001'002
#define C509_ERR_OID_DEC_MALFORMED 509'001'003

#define DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Type)                 \
    template <>                                                      \
    struct CBORCodec<Type>                                           \
    {                                                                \
        static bool encode(zcbor_state_t *state, const Type &input); \
        static bool decode(zcbor_state_t *state, Type &output);      \
    };

namespace C509
{
    template <typename T>
    struct CBORCodec;

    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Certificate)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(TBSCertificate)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(CertificateSerialNumber)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(AlgorithmIdentifier)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Name)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(Attribute)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(SubjectPublicKey)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(IssuerSignatureValue)
    DECLARE_C509_CBOR_CODEC_SPECIALIZATION(OID)
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