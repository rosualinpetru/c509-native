// #include "c509_codec_internal.hpp"

// using namespace C509::CRL;

// bool CBORCodec<RevokedCertificate>::encode(zcbor_state_t *state, const RevokedCertificate &input)
// {
//     if (!CBORCodec<CertificateSerialNumber>::encode(state, input.userCertificate))
//         ZCBOR_ERR(C509_ERR_REVOKEDCERT_ENC_SERIAL);

//     if (!CBORCodec<Time>::encode_unwrapped(state, input.revocationDate))
//         ZCBOR_ERR(C509_ERR_REVOKEDCERT_ENC_DATE);

//     if (!CBORCodec<Extensions>::encode(state, input.crlEntryExtensions))
//         ZCBOR_ERR(C509_ERR_REVOKEDCERT_ENC_EXT);

//     return true;
// }

// bool CBORCodec<RevokedCertificate>::decode(zcbor_state_t *state, RevokedCertificate &output)
// {
//     if (!CBORCodec<CertificateSerialNumber>::decode(state, output.userCertificate))
//         ZCBOR_ERR(C509_ERR_REVOKEDCERT_DEC_SERIAL);

//     if (!CBORCodec<Time>::decode_unwrapped(state, output.revocationDate))
//         ZCBOR_ERR(C509_ERR_REVOKEDCERT_DEC_DATE);

//     if (!CBORCodec<Extensions>::decode(state, output.crlEntryExtensions))
//         ZCBOR_ERR(C509_ERR_REVOKEDCERT_DEC_EXT);

//     return true;
// }
