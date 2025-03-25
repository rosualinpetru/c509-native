#ifndef C509_SUBJECT_PUBLIC_KEY_H
#define C509_SUBJECT_PUBLIC_KEY_H

#include <cstdint>

#include "structures.hpp"

/*
Algorithm	Public key
ML-DSA-44	1312
ML-DSA-65	1952
ML-DSA-87	2592

Curve	                    Public Key
Ed25519	                    32 bytes
Ed448	                    57 bytes
P-256	                    65 bytes
Brainpool P256r1 (bp256)	65 bytes
P-384	                    97 bytes
Brainpool P384r1 (bp384)	97 bytes


mldsa87_bp384: 2689 = 2592 + 97, round to 2700 for safety
*/
#define MAX_PK_BYTES 2700

namespace C509 {
    // "In general, the 'subjectPublicKey' BIT STRING value field is encoded as a CBOR byte string. This specification assumes the BIT STRING has zero unused bits and the unused bits byte is omitted. For rsaEncryption and id-ecPublicKey, the encoding of subjectPublicKey is further optimized"
    // https://www.ietf.org/arrchive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-3.1-3.7.1
    // RSA and ECC optimisations are not considered.
    struct PublicKey {
        bounded_array<uint8_t, MAX_PK_BYTES> bytes;

        std::string to_string() const;
    };
}

#endif // C509_SUBJECT_PUBLIC_KEY_H
