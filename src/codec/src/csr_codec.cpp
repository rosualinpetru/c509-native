#include "util/codec_internal.hpp"

using namespace C509;
using namespace C509::CSR;

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
    if (!zcbor_list_start_encode(state, 7))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_LIST_START);

    if (!CBORCodec<TBSCertificateRequest>::encode(state, input.tbsCertificateRequest))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_TBS);

    if (!C509::CBORCodec<SignatureValue>::encode(state, input.subjectSignatureValue))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_SIG);

    if (!zcbor_list_end_encode(state, 7))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_LIST_END);

    return true;
}

bool CSR::CBORCodec<C509CertificateRequest>::decode(zcbor_state_t *state, C509CertificateRequest &output) {
    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_LIST_START);

    if (!CBORCodec<TBSCertificateRequest>::decode(state, output.tbsCertificateRequest))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_TBS);

    if (!C509::CBORCodec<SignatureValue>::decode(state, output.subjectSignatureValue))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_SIG);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_LIST_END);

    return true;
}
