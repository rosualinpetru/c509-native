#ifndef __C509_EXTENSIONS_H
#define __C509_EXTENSIONS_H

#include "structures.hpp"

// WARNING
#define MAX_EXTENSION_BYTES 256

// WARNING
#define MAX_EXTENSIONS_LIST_SIZE 64

namespace C509
{
    struct Extension
    {
        enum class Type
        {
            // Int, // Not yet supported as requires implementation of optimised Extension CBOR encoding. Confer to the registry https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-12.html#section-9.4
            OID
        } type;

        struct
        {
            OID extensionID;
            bool critical;
            bounded_array<uint8_t, MAX_EXTENSION_BYTES> extensionValue;
        } oidExtension;
    };

    struct Extensions
    {
        enum class Type
        {
            MixedKeyUsage,
            List
        } type;

        union
        {
            int64_t mixedKeyUsage;
            bounded_array<Extension, MAX_EXTENSIONS_LIST_SIZE> extensions;
        };
    };
}

#endif // __C509_EXTENSIONS_H