#ifndef __C509_ISSUER_SIGNATURE_VALUE_H
#define __C509_ISSUER_SIGNATURE_VALUE_H

#include <cstdint>

#include "structures.hpp"

// TODO
#define MAX_SIG_BYTES 4096

namespace C509
{
    // TODO: Normally, optimisations are made for different kinds of keys like RSA and ECDSA, but
    // "In general, the 'signatureValue' BIT STRING value field is encoded as a CBOR byte string. This specification assumes the BIT STRING has zero unused bits and the unused bits byte is omitted. For rsaEncryption and id-ecPublicKey, the encoding of subjectPublicKey is further optimized"
    // https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-3.1-3.7.1
    // For now, only bstr keys are considered.
    struct SignatureValue
    {
        const bounded_array<uint8_t, MAX_SIG_BYTES> bytes;
    };
}

#endif // __C509_ISSUER_SIGNATURE_VALUE_H