#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<C509Certificate>::encode(zcbor_state_t *state, const C509Certificate &input)
{
    return zcbor_list_start_encode(state, 11) &&
           CBORCodec<TBSCertificate>::encode(state, input.tbsCertificate) &&
           CBORCodec<SignatureValue>::encode(state, input.signatureValue) &&
           zcbor_list_end_encode(state, 11);
}

bool CBORCodec<C509Certificate>::decode(zcbor_state_t *state, C509Certificate &output)
{
    return zcbor_list_start_decode(state) &&
           CBORCodec<TBSCertificate>::decode(state, output.tbsCertificate) &&
           CBORCodec<SignatureValue>::decode(state, output.signatureValue) &&
           zcbor_list_end_decode(state);
}

bool CBORCodec<TBSCertificate>::encode(zcbor_state_t *state, const TBSCertificate &input)
{
    if (input.c509CertificateType != 2 || !zcbor_uint32_put(state, 2))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_CERT_TYPE);

    if (!CBORCodec<CertificateSerialNumber>::encode(state, input.certificateSerialNumber))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SERIAL_NUMBER);

    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.issuerSignatureAlgorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_ISSUER_SIG_ALG);

    if (input.issuer.has_value)
    {
        if (!CBORCodec<Name>::encode(state, input.issuer.value)) // TODO: Additionally, encode as null if equal to subject.
            ZCBOR_ERR(C509_ERR_TBSCERT_ENC_ISSUER);
    }
    else if (!zcbor_nil_put(state, NULL))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_ISSUER_NIL);

    if (!CBORCodec<Time>::encode_unwrapped(state, input.validityNotBefore))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_VALIDITY_NOT_BEFORE);

    if (input.validityNotAfter.has_value && input.validityNotAfter.value.epochSeconds != 99991231235959)
    {
        if (!CBORCodec<Time>::encode_unwrapped(state, input.validityNotAfter.value))
            ZCBOR_ERR(C509_ERR_TBSCERT_ENC_VALIDITY_NOT_AFTER);
    }
    else if (!zcbor_nil_put(state, NULL))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_VALIDITY_NIL);

    if (!CBORCodec<Name>::encode(state, input.subject))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SUBJECT);

    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.subjectPublicKeyAlgorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SUBJ_PUBKEY_ALG);

    if (!CBORCodec<SubjectPublicKey>::encode(state, input.subjectPublicKey))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SUBJ_PUBKEY);

    if (!CBORCodec<Extensions>::encode(state, input.extensions))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_EXTENSIONS);

    return true;
}

bool CBORCodec<TBSCertificate>::decode(zcbor_state_t *state, TBSCertificate &output)
{
    if (!zcbor_uint32_expect(state, 2))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_CERT_TYPE);

    if (!CBORCodec<CertificateSerialNumber>::decode(state, output.certificateSerialNumber))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SERIAL_NUMBER);

    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.issuerSignatureAlgorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_ISSUER_SIG_ALG);

    if (zcbor_nil_expect(state, NULL))
        output.issuer.has_value = false;
    else
    {
        if (!CBORCodec<Name>::decode(state, output.issuer.value))
            ZCBOR_ERR(C509_ERR_TBSCERT_DEC_ISSUER);

        output.issuer.has_value = true;
    }

    if (!CBORCodec<Time>::decode_unwrapped(state, output.validityNotBefore))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_VALIDITY_NOT_BEFORE);

    if (zcbor_nil_expect(state, NULL))
        output.validityNotAfter.has_value = false;
    else
    {
        if (!CBORCodec<Time>::decode_unwrapped(state, output.validityNotAfter.value))
            ZCBOR_ERR(C509_ERR_TBSCERT_DEC_VALIDITY_NOT_AFTER);
        output.validityNotAfter.has_value = true;
    }

    if (!CBORCodec<Name>::decode(state, output.subject))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SUBJECT);

    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.subjectPublicKeyAlgorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SUBJ_PUBKEY_ALG);

    if (!CBORCodec<SubjectPublicKey>::decode(state, output.subjectPublicKey))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SUBJ_PUBKEY);

    if (!CBORCodec<Extensions>::decode(state, output.extensions))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_EXTENSIONS);

    return true;
}