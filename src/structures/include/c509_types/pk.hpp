#ifndef C509_SUBJECT_PUBLIC_KEY_H
#define C509_SUBJECT_PUBLIC_KEY_H

#include <cstdint>

#include "structures.hpp"

#define MAX_PK_BYTES 8192 // TODO

namespace C509 {
    // TODO: Normally, optimisations are made for different kinds of keys like RSA and ECDSA, but
    // "In general, the 'subjectPublicKey' BIT STRING value field is encoded as a CBOR byte string. This specification assumes the BIT STRING has zero unused bits and the unused bits byte is omitted. For rsaEncryption and id-ecPublicKey, the encoding of subjectPublicKey is further optimized"
    // https://www.ietf.org/arrchive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-3.1-3.7.1
    // For now, only bstr keys are considered.
    struct SubjectPublicKey {
        bounded_array<uint8_t, MAX_PK_BYTES> bytes;
    };
}

#endif // C509_SUBJECT_PUBLIC_KEY_H
