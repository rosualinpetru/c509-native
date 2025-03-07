#ifndef C509_PRIVATE_KEY_H
#define C509_PRIVATE_KEY_H

#include <cstdint>

#include "structures.hpp"

#include "algid.hpp"
#include "c509.hpp"

#define MAX_PRIV_KEY_BYTES 8192 // TODO

namespace C509 {
    // TODO: Normally, optimisations are made for different kinds of keys like RSA and ECDSA, but
    // https://www.ietf.org/arrchive/id/draft-ietf-cose-cbor-encoded-cert-12.html
    // For now, only bstr keys are considered.
    struct PrivateKey {
        bounded_array<uint8_t, MAX_PRIV_KEY_BYTES> bytes;
    };

    // Added for connecting private-public key pair
    // This depends actually on the algorithm and should be customised for different algorithms and be encoded
    // as CBOR instead of ASN.1 der. For ease of implementation, eliminating the need for public key reconstruction,
    // the raw public and private keys are extracted and stored in this structure - see 'core'.
    struct PrivateKeyInfo {
        PrivateKey private_key;
        PublicKey public_key;
    };

    struct C509PrivateKey {
        AlgorithmIdentifier subject_private_key_algorithm;
        PrivateKeyInfo subject_private_key_info;
    };

    struct C509PEM {
        C509PrivateKey private_key;
        optional<COSE_C509> cose_c509;
    };
}

#endif // C509_PRIVATE_KEY_H
