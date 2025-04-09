#include <string>

#include <openssl/objects.h>
#include <openssl/types.h>

#include "c509_core/c509.hpp"

bool map_alg_to_id(const std::string &algorithm, C509::AlgorithmIdentifier &identifier) {
    ASN1_OBJECT *obj = OBJ_txt2obj(algorithm.c_str(), 0); // Try name first

    if (!obj) {
        obj = OBJ_txt2obj(algorithm.c_str(), 1); // Try numeric form
        if (!obj) {
            return false;
        }
    }

    // Extract the OID's sub-identifiers
    uint8_t buf[128];
    int len = OBJ_obj2txt(reinterpret_cast<char *>(buf), sizeof(buf), obj, 1); // 1 = dotted OID
    ASN1_OBJECT_free(obj);

    if (len <= 0)
        return false;

    std::vector<uint32_t> subids;
    std::string oid_str(reinterpret_cast<char *>(buf), len);
    size_t start = 0, end;
    while ((end = oid_str.find('.', start)) != std::string::npos) {
        subids.push_back(std::stoul(oid_str.substr(start, end - start)));
        start = end + 1;
    }
    subids.push_back(std::stoul(oid_str.substr(start)));

    identifier.type = C509::AlgorithmIdentifier::Type::OID;
    identifier.oid_algorithm_identifier.algorithm_identifier.subids.copy(subids.data(), subids.size());
    identifier.oid_algorithm_identifier.parameters.reset();
    return true;
}

bool map_id_to_alg(std::string &algorithm, const C509::AlgorithmIdentifier &identifier) {
    const C509::OID *alg_oid = nullptr;
    if (identifier.type != C509::AlgorithmIdentifier::Type::OID) {
        return false;
    }

    alg_oid = &identifier.oid_algorithm_identifier.algorithm_identifier;

    // Convert C509::OID into dotted string
    std::ostringstream oss;
    for (size_t i = 0; i < alg_oid->subids.size(); ++i) {
        if (i > 0) oss << ".";
        oss << alg_oid->subids[i];
    }
    std::string oid_str = oss.str();

    // Convert OID string to ASN1_OBJECT and then to short name
    ASN1_OBJECT *obj = OBJ_txt2obj(oid_str.c_str(), 1); // 1 = dotted
    if (!obj) {
        return false;
    }

    char name_buf[128];
    int len = OBJ_obj2txt(name_buf, sizeof(name_buf), obj, 0); // 0 = get name if available
    ASN1_OBJECT_free(obj);

    if (len <= 0) {
        return false;
    }

    algorithm.assign(name_buf, len);
    return true;
}
