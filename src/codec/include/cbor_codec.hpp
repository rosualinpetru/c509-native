#ifndef __C509_CBOR_CODEC_H
#define __C509_CBOR_CODEC_H

#include <cstddef>
#include <cstdint>

namespace C509
{
    struct CBORState
    {
        uint8_t *data;
        size_t length;

        CBORState(uint8_t *data, size_t length) : data(data), length(length) {}
    };

    template <typename T>
    struct CBORCodec
    {
        static inline CBORState encode(const T &input);
        static inline T decode(const CBORState &input);
    };
}

#endif // __C509_CBOR_CODEC_H