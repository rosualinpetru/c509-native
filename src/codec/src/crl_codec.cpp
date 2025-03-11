#include "util/codec_internal.hpp"

using namespace C509;
using namespace C509::CRL;

bool CRL::CBORCodec<RevokedCertificate>::encode(zcbor_state_t *state, const RevokedCertificate &input) {
    if (!C509::CBORCodec<CertificateSerialNumber>::encode(state, input.user_certificate))
        ZCBOR_ERR(CRL_ERR_RVCERT_ENC_CSN);

    if (!C509::CBORCodec<Time>::encode_unwrapped(state, input.revocation_date))
        ZCBOR_ERR(CRL_ERR_RVCERT_ENC_DATE);

    if (!C509::CBORCodec<Extensions>::encode(state, input.crl_entry_extensions))
        ZCBOR_ERR(CRL_ERR_RVCERT_ENC_EXTS);

    return true;
}

bool CRL::CBORCodec<RevokedCertificate>::decode(zcbor_state_t *state, RevokedCertificate &output) {
    if (!C509::CBORCodec<CertificateSerialNumber>::decode(state, output.user_certificate))
        ZCBOR_ERR(CRL_ERR_RVCERT_DEC_CSN);

    if (!C509::CBORCodec<Time>::decode_unwrapped(state, output.revocation_date))
        ZCBOR_ERR(CRL_ERR_RVCERT_DEC_DATE);

    if (!C509::CBORCodec<Extensions>::decode(state, output.crl_entry_extensions))
        ZCBOR_ERR(CRL_ERR_RVCERT_DEC_EXTS);

    return true;
}

bool CRL::CBORCodec<TBSCertificateRevocationList>::encode(zcbor_state_t *state,
                                                          const TBSCertificateRevocationList &input) {
    if (!zcbor_uint32_put(state, input.c509_certificate_revocation_list_type))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_TYPE);

    if (!C509::CBORCodec<Name>::encode(state, input.issuer))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_ISSUER);

    if (!C509::CBORCodec<Time>::encode_unwrapped(state, input.this_update))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_THISUPDATE);

    if (!C509::CBORCodec<Time>::encode_unwrapped(state, input.next_update))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_NEXTUPDATE);

    if (!zcbor_list_start_encode(state, input.revoked_certificates.size()))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERTS_START);

    for (size_t i = 0; i < input.revoked_certificates.size(); i++)
        if (!CBORCodec<RevokedCertificate>::encode(state, input.revoked_certificates[i]))
            ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERT);

    if (!zcbor_list_end_encode(state, input.revoked_certificates.size()))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERTS_END);

    if (!C509::CBORCodec<Extensions>::encode(state, input.crl_extensions))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_EXTENSIONS);

    if (!C509::CBORCodec<AlgorithmIdentifier>::encode(state, input.issuer_signature_algorithm))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_SIG_ALG);

    return true;
}

bool CRL::CBORCodec<TBSCertificateRevocationList>::decode(zcbor_state_t *state, TBSCertificateRevocationList &output) {
    uint32_t int_value;
    if (!zcbor_uint32_decode(state, &int_value))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_TYPE);

    output.c509_certificate_revocation_list_type = int_value;

    if (!C509::CBORCodec<Name>::decode(state, output.issuer))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_ISSUER);

    if (!C509::CBORCodec<Time>::decode_unwrapped(state, output.this_update))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_THISUPDATE);

    if (!C509::CBORCodec<Time>::decode_unwrapped(state, output.next_update))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_NEXTUPDATE);

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERTS_START);

    bool r = zcbor_multi_decode(0, CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERT, output.revoked_certificates.len_p(),
                                reinterpret_cast<zcbor_decoder_t *>(CBORCodec<RevokedCertificate>::decode), state,
                                output.revoked_certificates.data_p(), sizeof(RevokedCertificate));

    if (!r)
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERT);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERTS_END);

    if (!C509::CBORCodec<Extensions>::decode(state, output.crl_extensions))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_EXTENSIONS);

    if (!C509::CBORCodec<AlgorithmIdentifier>::decode(state, output.issuer_signature_algorithm))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_SIG_ALG);

    return true;
}

bool CRL::CBORCodec<C509CertificateRevocationList>::encode(zcbor_state_t *state,
                                                           const C509CertificateRevocationList &input) {
    return zcbor_list_start_encode(state, 8) &&
           CBORCodec<TBSCertificateRevocationList>::encode(state, input.tbs_certificate_revocation_list) &&
           C509::CBORCodec<SignatureValue>::encode(state, input.issuer_signature_value) &&
           zcbor_list_end_encode(state, 8);
}

bool CRL::CBORCodec<
    C509CertificateRevocationList>::decode(zcbor_state_t *state, C509CertificateRevocationList &output) {
    return zcbor_list_start_decode(state) &&
           CBORCodec<TBSCertificateRevocationList>::decode(state, output.tbs_certificate_revocation_list) &&
           C509::CBORCodec<SignatureValue>::decode(state, output.issuer_signature_value) &&
           zcbor_list_end_decode(state);
}
