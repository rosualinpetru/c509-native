#ifndef C509_CORE_H
#define C509_CORE_H

#include <map>

#include "registry.hpp"

#define MAX_BUFFER_SIZE 16384

#include "c509_types/types.hpp"

bool map_alg_to_id(const std::string &algorithm, C509::AlgorithmIdentifier &identifier);

bool map_id_to_alg(std::string &algorithm, const C509::AlgorithmIdentifier &identifier);

bool key_gen(const std::string &algorithm, uint8_t *private_key_out, size_t &private_key_out_size);

bool csr_gen(const uint8_t *private_key, size_t private_key_size,
             std::map<uint32_t, std::string> &subject_attributes,
             std::map<std::vector<uint32_t>, std::tuple<bool, std::string> > &extensions,
             uint8_t *csr_out, size_t &csr_out_size);

bool csr_verify(const uint8_t *csr, size_t csr_size);

bool csr_sign(const uint8_t *csr, size_t csr_size, const uint8_t *private_key, size_t private_key_size,
              const uint8_t *ca_cert, size_t ca_cert_size, uint32_t days, uint64_t serial_number,
              uint8_t *cert_out, size_t &cert_out_size);

bool csr_self_sign(const uint8_t *csr, size_t csr_size, const uint8_t *private_key, size_t private_key_size,
                   uint32_t days, uint64_t serial_number, uint8_t *cert_out, size_t &cert_out_size);

bool crl_gen(const uint8_t *private_key, size_t private_key_size, const uint8_t *ca_cert, size_t ca_cert_size,
             uint32_t days, uint8_t *crl_out, size_t &crl_out_size);

bool crl_revoke(const uint8_t *private_key, size_t private_key_size, const uint8_t *ca_cert, size_t ca_cert_size,
                const uint8_t *crl_in, size_t crl_in_size, const uint8_t *cert_in, size_t cert_in_size, uint32_t days,
                uint8_t *crl_out, size_t &crl_out_size);

#endif // C509_CORE_H
