#ifndef C509_EXTENSIONS_H
#define C509_EXTENSIONS_H

#include <cstdint>

#include "structures.hpp"

#include "oid.hpp"

#define MAX_EXTENSION_BYTES 128 // TODO
#define MAX_EXTENSIONS_LIST_SIZE 32 // TODO

namespace C509 {
    struct Extension {
        enum class Type {
            // Int, // TODO: Not yet supported as requires implementation of optimised Extension CBOR encoding. Confer to the registry https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-9.4
            OID
        } type;

        struct {
            OID extension_id;
            bool critical;
            bounded_array<uint8_t, MAX_EXTENSION_BYTES> extension_value;
        } oidExtension;
    };

    struct Extensions {
        enum class Type {
            MixedKeyUsage,
            List
        } type{};

        union {
            int64_t mixed_key_usage{};
            bounded_array<Extension, MAX_EXTENSIONS_LIST_SIZE> extensions;
        };
    };
}

#endif // C509_EXTENSIONS_H
