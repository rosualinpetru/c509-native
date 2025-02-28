#include "util/codec_internal.hpp"

using namespace C509;
using namespace C509::CRL;

bool CRL::CBORCodec<RevokedCertificate>::encode(zcbor_state_t *state, const RevokedCertificate &input)
{
    if (!C509::CBORCodec<CertificateSerialNumber>::encode(state, input.userCertificate))
        ZCBOR_ERR(CRL_ERR_RVCERT_ENC_CSN);

    if (!C509::CBORCodec<Time>::encode_unwrapped(state, input.revocationDate))
        ZCBOR_ERR(CRL_ERR_RVCERT_ENC_DATE);

    if (!C509::CBORCodec<Extensions>::encode(state, input.crlEntryExtensions))
        ZCBOR_ERR(CRL_ERR_RVCERT_ENC_EXTS);

    return true;
}

bool CRL::CBORCodec<RevokedCertificate>::decode(zcbor_state_t *state, RevokedCertificate &output)
{
    if (!C509::CBORCodec<CertificateSerialNumber>::decode(state, output.userCertificate))
        ZCBOR_ERR(CRL_ERR_RVCERT_DEC_CSN);

    if (!C509::CBORCodec<Time>::decode_unwrapped(state, output.revocationDate))
        ZCBOR_ERR(CRL_ERR_RVCERT_DEC_DATE);

    if (!C509::CBORCodec<Extensions>::decode(state, output.crlEntryExtensions))
        ZCBOR_ERR(CRL_ERR_RVCERT_DEC_EXTS);

    return true;
}

bool CRL::CBORCodec<TBSCertificateRevocationList>::encode(zcbor_state_t *state, const TBSCertificateRevocationList &input)
{
    if (!zcbor_uint32_put(state, input.c509CertificateRevocationListType))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_TYPE);

    if (!C509::CBORCodec<Name>::encode(state, input.issuer))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_ISSUER);

    if (!C509::CBORCodec<Time>::encode_unwrapped(state, input.thisUpdate))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_THISUPDATE);

    if (!C509::CBORCodec<Time>::encode_unwrapped(state, input.nextUpdate))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_NEXTUPDATE);

    if (!zcbor_list_start_encode(state, input.revokedCertificates.len))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERTS_START);

    for (size_t i = 0; i < input.revokedCertificates.len; i++)
        if (!CBORCodec<RevokedCertificate>::encode(state, input.revokedCertificates.elements[i]))
            ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERT);

    if (!zcbor_list_end_encode(state, input.revokedCertificates.len))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERTS_END);

    if (!C509::CBORCodec<Extensions>::encode(state, input.crlExtensions))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_EXTENSIONS);

    if (!C509::CBORCodec<AlgorithmIdentifier>::encode(state, input.issuerSignatureAlgorithm))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_ENC_SIG_ALG);

    return true;
}

bool CRL::CBORCodec<TBSCertificateRevocationList>::decode(zcbor_state_t *state, TBSCertificateRevocationList &output)
{
    if (!zcbor_uint32_expect(state, output.c509CertificateRevocationListType))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_TYPE);

    if (!C509::CBORCodec<Name>::decode(state, output.issuer))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_ISSUER);

    if (!C509::CBORCodec<Time>::decode_unwrapped(state, output.thisUpdate))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_THISUPDATE);

    if (!C509::CBORCodec<Time>::decode_unwrapped(state, output.nextUpdate))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_NEXTUPDATE);

    if (!zcbor_list_start_decode(state))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERTS_START);

    bool r = zcbor_multi_decode(0, CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERT, &output.revokedCertificates.len, (zcbor_decoder_t *)CBORCodec<RevokedCertificate>::decode, state, output.revokedCertificates.elements, sizeof(RevokedCertificate));

    if (!r)
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERT);

    if (!zcbor_list_end_decode(state))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERTS_END);

    if (!C509::CBORCodec<Extensions>::decode(state, output.crlExtensions))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_EXTENSIONS);

    if (!C509::CBORCodec<AlgorithmIdentifier>::decode(state, output.issuerSignatureAlgorithm))
        ZCBOR_ERR(CRL_ERR_TBSCERTREVLIST_DEC_SIG_ALG);

    return true;
}

bool CRL::CBORCodec<C509CertificateRevocationList>::encode(zcbor_state_t *state, const C509CertificateRevocationList &input)
{
    if (!CBORCodec<TBSCertificateRevocationList>::encode(state, input.tbsCertificateRevocationList))
        ZCBOR_ERR(CRL_ERR_CERTREVLIST_ENC_TBS);

    if (!C509::CBORCodec<SignatureValue>::encode(state, input.issuerSignatureValue))
        ZCBOR_ERR(CRL_ERR_CERTREVLIST_ENC_SIG);

    return true;
}

bool CRL::CBORCodec<C509CertificateRevocationList>::decode(zcbor_state_t *state, C509CertificateRevocationList &output)
{
    if (!CBORCodec<TBSCertificateRevocationList>::decode(state, output.tbsCertificateRevocationList))
        ZCBOR_ERR(CRL_ERR_CERTREVLIST_DEC_TBS);

    if (!C509::CBORCodec<SignatureValue>::decode(state, output.issuerSignatureValue))
        ZCBOR_ERR(CRL_ERR_CERTREVLIST_DEC_SIG);

    return true;
}
