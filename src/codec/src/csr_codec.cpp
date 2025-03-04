#include "util/codec_internal.hpp"

using namespace C509;
using namespace C509::CSR;

bool CSR::CBORCodec<ChallengePassword>::encode(zcbor_state_t *state, const ChallengePassword &input) {
    // TODO
    // Aditional checks should be made for the content of the password:
    // https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-4-9
    // Not implemented yet

    switch (input.type) {
        case ChallengePassword::Type::TSTR:
            if (!zcbor_tstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.data()), input.bytes.size()))
                ZCBOR_ERR(CSR_ERR_CHLPSSWD_ENC_TSTR);

            return true;

        case ChallengePassword::Type::BSTR:
            if (!zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(input.bytes.data()), input.bytes.size()))
                ZCBOR_ERR(CSR_ERR_CHLPSSWD_ENC_BSTR);

            return true;

        default:
            ZCBOR_ERR(CSR_ERR_CHLPSSWD_ENC_UNSUPPORTED_TYPE);
    }
}

bool CSR::CBORCodec<ChallengePassword>::decode(zcbor_state_t *state, ChallengePassword &output) {
    zcbor_string str{};

    if (zcbor_tstr_decode(state, &str)) {
        if (str.len > MAX_CHALLENGE_PASSWORD_LEN)
            ZCBOR_ERR(CSR_ERR_CHLPSSWD_DEC_INVALID_LENGTH);

        if (!output.bytes.copy(str.value, str.len))
            ZCBOR_ERR(CSR_ERR_CHLPSSWD_DEC_BUFFER_ERROR);

        return true;
    }
    if (!zcbor_bstr_decode(state, &str))
        ZCBOR_ERR(CSR_ERR_CHLPSSWD_DEC_BSTR);

    if (str.len > MAX_CHALLENGE_PASSWORD_LEN)
        ZCBOR_ERR(CSR_ERR_CHLPSSWD_DEC_INVALID_LENGTH);

    if (!output.bytes.copy(str.value, str.len))
        ZCBOR_ERR(CSR_ERR_CHLPSSWD_DEC_BUFFER_ERROR);

    return true;
}

bool CSR::CBORCodec<TBSCertificateRequest>::encode(zcbor_state_t *state, const TBSCertificateRequest &input) {
    if (input.c509CertificateRequestType != 0 || !zcbor_uint32_put(state, 0))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_TYPE);


    if (!C509::CBORCodec<AlgorithmIdentifier>::encode(state, input.subjectSignatureAlgorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_SIG_ALG);

    if (!C509::CBORCodec<Name>::encode(state, input.subject))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_SUBJECT);

    if (!C509::CBORCodec<AlgorithmIdentifier>::encode(state, input.subjectPublicKeyAlgorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_PUBKEY_ALG);

    if (!C509::CBORCodec<SubjectPublicKey>::encode(state, input.subjectPublicKey))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_PUBKEY);

    if (!C509::CBORCodec<Extensions>::encode(state, input.extensionsRequest))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_EXTENSIONS);

    return true;
}

bool CSR::CBORCodec<TBSCertificateRequest>::decode(zcbor_state_t *state, TBSCertificateRequest &output) {
    if (!zcbor_uint32_expect(state, 0))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_TYPE);

    output.c509CertificateRequestType = 0;

    if (!C509::CBORCodec<AlgorithmIdentifier>::decode(state, output.subjectSignatureAlgorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_SIG_ALG);

    if (!C509::CBORCodec<Name>::decode(state, output.subject))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_SUBJECT);

    if (!C509::CBORCodec<AlgorithmIdentifier>::decode(state, output.subjectPublicKeyAlgorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_PUBKEY_ALG);

    if (!C509::CBORCodec<SubjectPublicKey>::decode(state, output.subjectPublicKey))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_PUBKEY);

    if (!C509::CBORCodec<Extensions>::decode(state, output.extensionsRequest))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_EXTENSIONS);

    return true;
}

bool CSR::CBORCodec<C509CertificateRequest>::encode(zcbor_state_t *state, const C509CertificateRequest &input) {
    if (!CBORCodec<TBSCertificateRequest>::encode(state, input.tbsCertificateRequest))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_TBS);

    if (!C509::CBORCodec<SignatureValue>::encode(state, input.subjectSignatureValue))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_SIG);

    if (input.challengePassword.has()) {
        if (!CBORCodec<ChallengePassword>::encode(state, input.challengePassword.get()))
            ZCBOR_ERR(CSR_ERR_REQ_ENC_CHALLENGE);
    } else if (!zcbor_nil_put(state, nullptr))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_CHALLENGE_NIL);

    return true;
}

bool CSR::CBORCodec<C509CertificateRequest>::decode(zcbor_state_t *state, C509CertificateRequest &output) {
    if (!CBORCodec<TBSCertificateRequest>::decode(state, output.tbsCertificateRequest))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_TBS);

    if (!C509::CBORCodec<SignatureValue>::decode(state, output.subjectSignatureValue))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_SIG);

    if (zcbor_nil_expect(state, nullptr))
        output.challengePassword.reset();
    else {
        if (!CBORCodec<ChallengePassword>::decode(state, output.challengePassword.get()))
            ZCBOR_ERR(CSR_ERR_REQ_DEC_CHALLENGE);

        output.challengePassword.set_has();
    }

    return true;
}
