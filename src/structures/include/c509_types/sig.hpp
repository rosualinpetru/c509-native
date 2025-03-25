#ifndef C509_ISSUER_SIGNATURE_VALUE_H
#define C509_ISSUER_SIGNATURE_VALUE_H

#include <cstdint>

#include "structures.hpp"

/*
Algorithm Signature
ML-DSA-44 2420
ML-DSA-65 3309
ML-DSA-87 4627

Curve	                    Signature
Ed25519	                    64 bytes
Ed448	                    114 bytes
P-256	                    64 bytes
Brainpool P256r1 (bp256)	64 bytes
P-384	                    96 bytes
Brainpool P384r1 (bp384)	96 bytes


mldsa87_ed448: 4765 determined empirically
*/
#define MAX_SIG_BYTES 4765

namespace C509 {
    // "In general, the 'signatureValue' BIT STRING value field is encoded as a CBOR byte string. This specification assumes the BIT STRING has zero unused bits and the unused bits byte is omitted. For rsaEncryption and id-ecPublicKey, the encoding of subjectPublicKey is further optimized"
    // https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-3.1-3.7.1
    // RSA and ECC optimisations are not considered
    struct SignatureValue {
        bounded_array<uint8_t, MAX_SIG_BYTES> bytes;

        std::string to_string() const;
    };
}

#endif // C509_ISSUER_SIGNATURE_VALUE_H
