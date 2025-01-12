/*
 * Generated using zcbor version 0.9.99-2b837d1
 * https://github.com/NordicSemiconductor/zcbor
 * at: 2025-01-12 19:18:44
 * Generated with a --default-max-qty of 1024
 */

#ifndef GEN_ENCODE_H__
#define GEN_ENCODE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <c509_common.hpp>

#ifdef __cplusplus
extern "C" {
#endif

#if DEFAULT_MAX_QTY != 1024
#error "The type file was generated with a different default_max_qty than this file"
#endif


int cbor_encode_All(
		uint8_t *payload, size_t payload_len,
		const struct All *input,
		size_t *payload_len_out);


#ifdef __cplusplus
}
#endif

#endif /* GEN_ENCODE_H__ */
