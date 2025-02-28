#include <cstddef>

#include "util/codec_internal.hpp"

#include <catch2/catch_tostring.hpp>
#include <sstream>
#include <iomanip>

struct HexByte
{
    uint8_t value;
    explicit HexByte(uint8_t v) : value(v) {}
    bool operator==(const HexByte &other) const { return value == other.value; }
};

namespace Catch
{
    template <>
    struct StringMaker<HexByte>
    {
        static std::string convert(HexByte hb)
        {
            std::ostringstream oss;
            oss << "0x"
                << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                << static_cast<int>(hb.value);
            return oss.str();
        }
    };
}

class CodecTestHelper
{
public:
    CodecTestHelper(size_t state_count, size_t elem_count, zcbor_decoder_t *encode_fn, zcbor_decoder_t *decode_fn)
        : state(state_count), elem_count(elem_count), encode_fn(encode_fn), decode_fn(decode_fn) {}

    int encode(uint8_t *payload, size_t payload_len, const void *input, size_t *payload_len_out)
    {
        return zcbor_entry_function(
            payload,
            payload_len,
            (void *)input,
            payload_len_out,
            state.data(),
            encode_fn,
            state.size(),
            elem_count);
    }

    int decode(const uint8_t *payload, size_t payload_len, void *result, size_t *payload_len_out)
    {
        return zcbor_entry_function(
            payload,
            payload_len,
            result,
            payload_len_out,
            state.data(),
            decode_fn,
            state.size(),
            elem_count);
    }

private:
    std::vector<zcbor_state_t> state;
    size_t elem_count;
    zcbor_decoder_t *encode_fn;
    zcbor_decoder_t *decode_fn;
};