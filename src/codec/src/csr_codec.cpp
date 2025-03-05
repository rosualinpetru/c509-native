#include "util/codec_internal.hpp"

using namespace C509;
using namespace C509::CSR;

bool CSR::CBORCodec<TBSCertificateRequest>::encode(zcbor_state_t *state, const TBSCertificateRequest &input) {
    if (input.c509_certificate_request_type != 0 || !zcbor_uint32_put(state, 0))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_TYPE);

    if (!C509::CBORCodec<AlgorithmIdentifier>::encode(state, input.subject_signature_algorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_SIG_ALG);

    if (!C509::CBORCodec<Name>::encode(state, input.subject))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_SUBJECT);

    if (!C509::CBORCodec<AlgorithmIdentifier>::encode(state, input.subject_public_key_algorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_PUBKEY_ALG);

    if (!C509::CBORCodec<SubjectPublicKey>::encode(state, input.subject_public_key))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_PUBKEY);

    if (!C509::CBORCodec<Extensions>::encode(state, input.extensions_request))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_ENC_EXTENSIONS);

    return true;
}

bool CSR::CBORCodec<TBSCertificateRequest>::decode(zcbor_state_t *state, TBSCertificateRequest &output) {
    if (!zcbor_uint32_expect(state, 0))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_TYPE);

    output.c509_certificate_request_type = 0;

    if (!C509::CBORCodec<AlgorithmIdentifier>::decode(state, output.subject_signature_algorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_SIG_ALG);

    if (!C509::CBORCodec<Name>::decode(state, output.subject))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_SUBJECT);

    if (!C509::CBORCodec<AlgorithmIdentifier>::decode(state, output.subject_public_key_algorithm))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_PUBKEY_ALG);

    if (!C509::CBORCodec<SubjectPublicKey>::decode(state, output.subject_public_key))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_PUBKEY);

    if (!C509::CBORCodec<Extensions>::decode(state, output.extensions_request))
        ZCBOR_ERR(CSR_ERR_TBSCERTREQ_DEC_EXTENSIONS);

    return true;
}

bool CSR::CBORCodec<C509CertificateRequest>::encode(zcbor_state_t *state, const C509CertificateRequest &input) {
    if (!zcbor_list_start_encode(state, 7))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_LIST_START);

    if (!CBORCodec<TBSCertificateRequest>::encode(state, input.tbs_certificate_request))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_TBS);

    if (!C509::CBORCodec<SignatureValue>::encode(state, input.subject_signature_value))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_SIG);

    if (!zcbor_list_end_encode(state, 7))
        ZCBOR_ERR(CSR_ERR_REQ_ENC_LIST_END);

    return true;
}

bool CSR::CBORCodec<C509CertificateRequest>::decode(zcbor_state_t *state, C509CertificateRequest &output) {
    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_LIST_START);

    if (!CBORCodec<TBSCertificateRequest>::decode(state, output.tbs_certificate_request))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_TBS);

    if (!C509::CBORCodec<SignatureValue>::decode(state, output.subject_signature_value))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_SIG);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(CSR_ERR_REQ_DEC_LIST_END);

    return true;
}
