#ifndef __C509_C509_CODEC_H
#define __C509_C509_CODEC_H

#include "c509_types.hpp"

namespace C509
{
    int encode(uint8_t *payload, size_t payload_len, const C509Certificate *input, size_t *payload_len_out);
    int decode(const uint8_t *payload, size_t payload_len, C509Certificate *result, size_t *payload_len_out);
}

#endif // __C509_C509_CODEC_H