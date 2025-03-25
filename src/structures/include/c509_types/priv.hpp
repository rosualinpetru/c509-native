#ifndef C509_PRIVATE_KEY_H
#define C509_PRIVATE_KEY_H

#include <cstdint>

#include "structures.hpp"

#include "algid.hpp"
#include "c509.hpp"

/*

Algorithm	Private key
ML-DSA-44	32 or 2560 or 2592
ML-DSA-65	32 or 4032 or 4064
ML-DSA-87	32 or 4896 or 4928

Curve	                    Private Key
Ed25519	                    32 bytes
Ed448	                    57 bytes
P-256	                    32 bytes
Brainpool P256r1 (bp256)	32 bytes
P-384	                    48 bytes
Brainpool P384r1 (bp384)	48 bytes


Worst case: 4985 = 4928 + 57
*/

#define MAX_PRIV_KEY_BYTES 4985

namespace C509 {
    // https://www.ietf.org/arrchive/id/draft-ietf-cose-cbor-encoded-cert-12.html
    // RSA and ECC optimisations are not considered
    struct PrivateKey {
        bounded_array<uint8_t, MAX_PRIV_KEY_BYTES> bytes;

        std::string to_string() const;
    };

    // Added for connecting private-public key pair
    // This depends actually on the algorithm and should be customised for different algorithms and be encoded
    // as CBOR instead of ASN.1 der. For ease of implementation, eliminating the need for public key reconstruction,
    // the raw public and private keys are extracted and stored in this structure - see 'core'.
    struct PrivateKeyInfo {
        PrivateKey private_key;
        PublicKey public_key;

        std::string to_string() const;
    };

    struct C509PrivateKey {
        AlgorithmIdentifier subject_private_key_algorithm;
        PrivateKeyInfo subject_private_key_info;

        std::string to_string() const;
    };

    struct C509PEM {
        C509PrivateKey private_key;
        optional<COSE_C509> cose_c509;

        std::string to_string() const;
    };
}

#endif // C509_PRIVATE_KEY_H
