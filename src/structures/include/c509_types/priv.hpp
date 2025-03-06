#ifndef C509_PRIVATE_KEY_H
#define C509_PRIVATE_KEY_H

#include <cstdint>

#include "structures.hpp"

#include "algid.hpp"

#define MAX_PRIV_KEY_BYTES 8192 // TODO

namespace C509 {
    // TODO: Normally, optimisations are made for different kinds of keys like RSA and ECDSA, but
    // https://www.ietf.org/arrchive/id/draft-ietf-cose-cbor-encoded-cert-12.html
    // For now, only bstr keys are considered.
    struct C509PrivateKey {
        AlgorithmIdentifier subject_private_key_algorithm;
        bounded_array<uint8_t, MAX_PRIV_KEY_BYTES> subject_private_key;
        bounded_array<uint8_t, MAX_PRIV_KEY_BYTES> subject_public_key;
        // TODO: for ease of implementation in `core`, the public key is also stored because derivation does not occur
    };
}

#endif // C509_PRIVATE_KEY_H
