#ifndef C509_ALGID_MAPPER_H
#define C509_ALGID_MAPPER_H

#include <string>

#include "c509_types/types.hpp"

namespace C509 {
    bool algid_mapper(const std::string &algorithm, AlgorithmIdentifier &identifier);
}

#endif // C509_ALGID_MAPPER_H
