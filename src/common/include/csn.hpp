#ifndef __C509_CERTIFICATE_SERIAL_NUMBER_H
#define __C509_CERTIFICATE_SERIAL_NUMBER_H

#include <cstddef>
#include <cstdint>

#include "util.hpp"

namespace C509
{
    // taken from https://datatracker.ietf.org/doc/html/rfc5280#section-4.1.2.2
    constexpr size_t MAX_CERTIFICATE_SERIAL_NUMBER_BYTES = 20;

    struct CertificateSerialNumber
    {
        const array<uint8_t, MAX_CERTIFICATE_SERIAL_NUMBER_BYTES> biguint;
    };
}

#endif // __C509_CERTIFICATE_SERIAL_NUMBER_H
