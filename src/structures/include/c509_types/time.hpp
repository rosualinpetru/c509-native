#ifndef C509_TIME_H
#define C509_TIME_H

#include <cstdint>

namespace C509 {
    struct Time {
        uint64_t epoch_seconds;

        std::string to_string() const;
    };
}

#endif // C509_TIME_H
