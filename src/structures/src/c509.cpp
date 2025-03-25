#include "c509_types/c509.hpp"

#include <sstream>

std::string C509::COSE_C509::to_string() const {
    std::ostringstream oss;
    oss << "COSE_C509:\n";
    if (certificates.empty()) {
        oss << "  <No Certificates>";
    } else {
        for (size_t i = 0; i < certificates.size(); ++i) {
            if (i > 0) oss << "\n";
            oss << "  Certificate[" << i + 1 << "]:\n" << certificates[i].to_string();
        }
    }
    return oss.str();
}
