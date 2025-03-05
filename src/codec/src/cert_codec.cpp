#include "util/codec_internal.hpp"

using namespace C509;

bool CBORCodec<C509Certificate>::encode(zcbor_state_t *state, const C509Certificate &input) {
    return zcbor_list_start_encode(state, 11) &&
           CBORCodec<TBSCertificate>::encode(state, input.tbs_certificate) &&
           CBORCodec<SignatureValue>::encode(state, input.signature_value) &&
           zcbor_list_end_encode(state, 11);
}

bool CBORCodec<C509Certificate>::decode(zcbor_state_t *state, C509Certificate &output) {
    return zcbor_list_start_decode(state) &&
           CBORCodec<TBSCertificate>::decode(state, output.tbs_certificate) &&
           CBORCodec<SignatureValue>::decode(state, output.signature_value) &&
           zcbor_list_end_decode(state);
}

bool CBORCodec<TBSCertificate>::encode(zcbor_state_t *state, const TBSCertificate &input) {
    if (input.c509_certificate_type != 2 || !zcbor_uint32_put(state, 2))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_CERT_TYPE);

    if (!CBORCodec<CertificateSerialNumber>::encode(state, input.certificate_serial_number))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SERIAL_NUMBER);

    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.issuer_signature_algorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_ISSUER_SIG_ALG);

    if (input.issuer.has()) {
        if (!CBORCodec<Name>::encode(state, input.issuer.get()))
            // TODO: Additionally, encode as null if equal to subject.
            ZCBOR_ERR(C509_ERR_TBSCERT_ENC_ISSUER);
    } else if (!zcbor_nil_put(state, nullptr))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_ISSUER_NIL);

    if (!CBORCodec<Time>::encode_unwrapped(state, input.validity_not_before))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_VALIDITY_NOT_BEFORE);

    if (input.validity_not_after.has() && input.validity_not_after.get().epoch_seconds != 99991231235959) {
        if (!CBORCodec<Time>::encode_unwrapped(state, input.validity_not_after.get()))
            ZCBOR_ERR(C509_ERR_TBSCERT_ENC_VALIDITY_NOT_AFTER);
    } else if (!zcbor_nil_put(state, nullptr))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_VALIDITY_NIL);

    if (!CBORCodec<Name>::encode(state, input.subject))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SUBJECT);

    if (!CBORCodec<AlgorithmIdentifier>::encode(state, input.subject_public_key_algorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SUBJ_PUBKEY_ALG);

    if (!CBORCodec<SubjectPublicKey>::encode(state, input.subject_public_key))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_SUBJ_PUBKEY);

    if (!CBORCodec<Extensions>::encode(state, input.extensions))
        ZCBOR_ERR(C509_ERR_TBSCERT_ENC_EXTENSIONS);

    return true;
}

bool CBORCodec<TBSCertificate>::decode(zcbor_state_t *state, TBSCertificate &output) {
    if (!zcbor_uint32_expect(state, 2))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_CERT_TYPE);

    output.c509_certificate_type = 2;

    if (!CBORCodec<CertificateSerialNumber>::decode(state, output.certificate_serial_number))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SERIAL_NUMBER);

    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.issuer_signature_algorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_ISSUER_SIG_ALG);

    if (zcbor_nil_expect(state, nullptr))
        output.issuer.reset();
    else {
        if (!CBORCodec<Name>::decode(state, output.issuer.get()))
            ZCBOR_ERR(C509_ERR_TBSCERT_DEC_ISSUER);

        output.issuer.set_has();
    }

    if (!CBORCodec<Time>::decode_unwrapped(state, output.validity_not_before))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_VALIDITY_NOT_BEFORE);

    if (zcbor_nil_expect(state, nullptr))
        output.validity_not_after.reset();
    else {
        if (!CBORCodec<Time>::decode_unwrapped(state, output.validity_not_after.get()))
            ZCBOR_ERR(C509_ERR_TBSCERT_DEC_VALIDITY_NOT_AFTER);
        output.validity_not_after.set_has();
    }

    if (!CBORCodec<Name>::decode(state, output.subject))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SUBJECT);

    if (!CBORCodec<AlgorithmIdentifier>::decode(state, output.subject_public_key_algorithm))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SUBJ_PUBKEY_ALG);

    if (!CBORCodec<SubjectPublicKey>::decode(state, output.subject_public_key))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_SUBJ_PUBKEY);

    if (!CBORCodec<Extensions>::decode(state, output.extensions))
        ZCBOR_ERR(C509_ERR_TBSCERT_DEC_EXTENSIONS);

    return true;
}
