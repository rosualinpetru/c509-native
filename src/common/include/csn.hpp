#ifndef __C509_CERTIFICATE_SERIAL_NUMBER_H
#define __C509_CERTIFICATE_SERIAL_NUMBER_H

#include <cstdint>

#include "structures.hpp"

// Defined in https://datatracker.ietf.org/doc/html/rfc5280#section-4.1.2.2
#define MAX_CSN_BYTES 20

namespace C509
{
    struct CertificateSerialNumber
    {
        bounded_array<uint8_t, MAX_CSN_BYTES> bytes;
    };
}

#endif // __C509_CERTIFICATE_SERIAL_NUMBER_H
