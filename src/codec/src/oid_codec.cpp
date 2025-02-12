// #include "cbor_codec.hpp"

// #include <zcbor_encode.h>
// #include <zcbor_decode.h>
// #include <zcbor_print.h>
// #include <cstring> // For memcpy

// namespace C509
// {
//     bool CBORCodec<OID>::encode(zcbor_state_t *state, const OID &input)
//     {
//         zcbor_log("%s\r\n", __func__);

//         if (input.size > MAX_OID_SUBIDS)
//         {
//             zcbor_error(state, 509002);
//             return false;
//         }

//         uint8_t oid_bytes[MAX_OID_SUBIDS * sizeof(uint32_t)];
//         size_t byte_len = input.size * sizeof(uint32_t);

//         std::memcpy(oid_bytes, input.subids, byte_len);

//         bool res = zcbor_bstr_encode_ptr(state, reinterpret_cast<const char *>(oid_bytes), byte_len);

//         log_result(state, res, __func__);
//         return res;
//     }

//     bool CBORCodec<OID>::decode(zcbor_state_t *state, OID &output)
//     {
//         zcbor_log("%s\r\n", __func__);

//         zcbor_string str;
//         bool res = zcbor_bstr_decode(state, &str);

//         if (str.len % sizeof(uint32_t) != 0 || (str.len / sizeof(uint32_t)) > MAX_OID_SUBIDS)
//         {
//             zcbor_error(state, 509003);
//             log_result(state, false, __func__);
//             return false;
//         }

//         output.subids = reinterpret_cast<const uint32_t *>(str.value);
//         output.size = str.len / sizeof(uint32_t);

//         log_result(state, res, __func__);
//         return res;
//     }

// }
