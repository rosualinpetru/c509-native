#include "c509_codec_internal.hpp"

#define MAX_ENCODED_OID_LEN MAX_OID_SUBIDS * 5 // Worst case: each subid uses up to 5 bytes

using namespace C509;

bool CBORCodec<OID>::encode_unwrapped(zcbor_state_t *state, const OID &input)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    if (input.subids.len < 2 || input.subids.len > MAX_OID_SUBIDS)
        fail("OID must have at least two sub-identifiers and at max 128", C509_ERR_OID_ENC_INVALID_LENGTH);

    uint8_t oid_bytes[MAX_ENCODED_OID_LEN];
    size_t oid_len = 0;

    // Encode first two sub-identifiers
    uint32_t first_byte = (input.subids.elements[0] * 40) + input.subids.elements[1];
    oid_bytes[oid_len++] = static_cast<uint8_t>(first_byte);

    // Encode the remaining sub-identifiers using base-128 encoding
    for (size_t i = 2; i < input.subids.len; i++)
    {
        uint32_t value = input.subids.elements[i];
        uint8_t base128[5] = {0}; // Max 5 bytes needed for a 32-bit integer
        size_t base128_len = 0;

        do
        {
            base128[base128_len++] = (value & 0x7F) | 0x80;
            value >>= 7;
        } while (value > 0);

        base128[0] &= 0x7F; // Clear MSB of last byte

        // Reverse order
        for (size_t j = 0; j < base128_len; ++j)
            oid_bytes[oid_len++] = base128[base128_len - 1 - j];
    }

    bool res = zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(oid_bytes), oid_len);

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}

bool CBORCodec<OID>::decode_unwrapped(zcbor_state_t *state, OID &output)
{
    zcbor_log("%s\r\n", __PRETTY_FUNCTION__);

    zcbor_string str;
    bool res;

    if (!(res = zcbor_bstr_decode(state, &str)))
        fail("OID byte string decoding failed", C509_ERR_OID_DEC_BSTR_FAILED);

    if (str.len < 1 || str.len > MAX_ENCODED_OID_LEN)
        fail("Invalid OID encoding length", C509_ERR_OID_DEC_INVALID_LENGTH);

    uint8_t first_byte = str.value[0];
    output.subids.elements[0] = first_byte / 40;
    output.subids.elements[1] = first_byte % 40;
    output.subids.len = 2;

    // Decode remaining sub-identifiers using base-128 decoding
    size_t index = 1;
    while (index < str.len)
    {
        uint32_t value = 0;
        uint8_t byte;
        do
        {
            if (index >= str.len)
                fail("Malformed OID: unexpected end of data", C509_ERR_OID_DEC_MALFORMED);

            byte = str.value[index++];
            value = (value << 7) | (byte & 0x7F);
        } while (byte & 0x80); // Continue while MSB is set

        output.subids.elements[output.subids.len++] = value;
    }

    log_result(state, res, __PRETTY_FUNCTION__);
    return res;
}
