#ifndef C509_COSE_C509_H
#define C509_COSE_C509_H

#include "structures.hpp"

#include "cert.hpp"

#define MAX_C509_BAG 10 // TODO

namespace C509 {
    struct COSE_C509 {
        bounded_array<C509Certificate, MAX_C509_BAG> certificates;

        std::string to_string() const;
    };
}

#endif // C509_COSE_C509_H
