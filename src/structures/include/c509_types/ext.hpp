#ifndef C509_EXTENSIONS_H
#define C509_EXTENSIONS_H

#include <cstdint>

#include "structures.hpp"

#include "oid.hpp"

#define MAX_EXTENSION_BYTES 1024 // Warning: The number of bytes is considered as a worst case scenario.
#define MAX_EXTENSIONS_LIST_SIZE 30 // https://datatracker.ietf.org/doc/html/rfc5280#section-4.1.2.4, (1..MAX), consider MAX = 30 (number of extensions in the C509 registry)



namespace C509 {
    struct Extension {
        enum class Type {
            Int,
            // TODO: Only a subset of C509 is supported. Confer to the registry https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-9.4
            OID
        } type;

        union {
            struct {
                int16_t extension_id;
                void *extension;
            } int_extension{};

            struct {
                OID extension_id;
                bool critical;
                bounded_array<uint8_t, MAX_EXTENSION_BYTES> extension_value;
            } oid_extension;
        };

        std::string to_string() const;
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

        std::string to_string() const;
    };

    struct KeyUsage {
        uint8_t value = 0;

        enum UsageBit {
            digitalSignature = 0,
            nonRepudiation = 1,
            keyEncipherment = 2,
            dataEncipherment = 3,
            keyAgreement = 4,
            keyCertSign = 5,
            cRLSign = 6,
            encipherOnly = 7,
            decipherOnly = 8
        };

        KeyUsage(std::initializer_list<UsageBit> usages) {
            for (const UsageBit bit: usages) {
                value |= (1 << bit);
            }
        }

        std::string to_string() const;
    };

    struct BasicConstraints {
        int8_t value;

        std::string to_string() const;
    };

    struct SubjectKeyIdentifier {
        bounded_array<uint8_t, 20> value;

        std::string to_string() const;
    };
}

#endif // C509_EXTENSIONS_H
