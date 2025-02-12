#ifndef __C509_CERTIFICATE_SERIAL_NUMBER_H
#define __C509_CERTIFICATE_SERIAL_NUMBER_H

#include <cstddef>
#include <cstdint>

#include "util.hpp"

namespace C509
{
    // Defined in https://datatracker.ietf.org/doc/html/rfc5280#section-4.1.2.2
    constexpr size_t MAX_CSN_BYTES = 20;

    struct CertificateSerialNumber
    {
        const bounded_array<uint8_t, MAX_CSN_BYTES> bytes;
    };
}

#endif // __C509_CERTIFICATE_SERIAL_NUMBER_H
