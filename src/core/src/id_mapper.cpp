#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <optional>
#include <cstdint>
#include <algorithm>

#include <openssl/objects.h>
#include <openssl/types.h>

#include "c509_core/c509.hpp"

static const std::unordered_map<std::string, std::string> kNameToOID_Signature = {
    {"mldsa44", "2.16.840.1.101.3.4.3.17"},
    {"p256_mldsa44", "1.3.9999.7.5"},
    {"rsa3072_mldsa44", "1.3.9999.7.6"},
    {"mldsa65", "2.16.840.1.101.3.4.3.18"},
    {"p384_mldsa65", "1.3.9999.7.7"},
    {"mldsa87", "2.16.840.1.101.3.4.3.19"},
    {"p521_mldsa87", "1.3.9999.7.8"},
};

static const std::unordered_map<std::string, std::string> kNameToOID_KEM = {
    {"mlkem512", "2.16.840.1.101.3.4.4.1"},
    {"p256_mlkem512", "1.3.6.1.4.1.22554.5.7.1"},
    {"x25519_mlkem512", "1.3.6.1.4.1.22554.5.8.1"},
    {"mlkem768", "2.16.840.1.101.3.4.4.2"},
    {"mlkem1024", "2.16.840.1.101.3.4.4.3"},
    {"SecP384r1MLKEM1024", "1.3.6.1.4.1.42235.6"},
};

struct C509PkEntry
{
    int value;
    const char *name;
    const char *oid;
};
static constexpr C509PkEntry kC509PublicKeyTable[] = {
    {0, "rsaEncryption", "1.2.840.113549.1.1.1"},
    {1, "ecPublicKey-secp256r1", "1.2.840.10045.2.1"},
    {2, "ecPublicKey-secp384r1", "1.2.840.10045.2.1"},
    {3, "ecPublicKey-secp521r1", "1.2.840.10045.2.1"},
    {8, "X25519", "1.3.101.110"},
    {9, "X448", "1.3.101.111"},
    {10, "Ed25519", "1.3.101.112"},
    {11, "Ed448", "1.3.101.113"},
    {24, "ecPublicKey-brainpoolP256r1", "1.2.840.10045.2.1"},
    {25, "ecPublicKey-brainpoolP384r1", "1.2.840.10045.2.1"},
    {26, "ecPublicKey-brainpoolP512r1", "1.2.840.10045.2.1"},
    {27, "ecPublicKey-FRP256v1", "1.2.840.10045.2.1"},
    {28, "ecPublicKey-sm2p256v1", "1.2.840.10045.2.1"},
};

struct C509SigEntry
{
    int value;
    const char *name;
    const char *oid;
};
static constexpr C509SigEntry kC509SignatureTable[] = {
    {-256, "sha1WithRSAEncryption", "1.2.840.113549.1.1.5"},
    {-255, "ecdsa-with-SHA1", "1.2.840.10045.4.1"},
    {0, "ecdsa-with-SHA256", "1.2.840.10045.4.3.2"},
    {1, "ecdsa-with-SHA384", "1.2.840.10045.4.3.3"},
    {2, "ecdsa-with-SHA512", "1.2.840.10045.4.3.4"},
    {3, "ecdsa-with-SHAKE128", "1.3.6.1.5.5.7.6.32"},
    {4, "ecdsa-with-SHAKE256", "1.3.6.1.5.5.7.6.33"},
    {12, "Ed25519", "1.3.101.112"},
    {13, "Ed448", "1.3.101.113"},
    {14, "sa-ecdhPop-sha256-hmac-sha256", "1.3.6.1.5.5.7.6.26"},
    {15, "sa-ecdhPop-sha384-hmac-sha384", "1.3.6.1.5.5.7.6.27"},
    {16, "sa-ecdhPop-sha512-hmac-sha512", "1.3.6.1.5.5.7.6.28"},
    {23, "sha256WithRSAEncryption", "1.2.840.113549.1.1.11"},
    {24, "sha384WithRSAEncryption", "1.2.840.113549.1.1.12"},
    {25, "sha512WithRSAEncryption", "1.2.840.113549.1.1.13"},
    {26, "RSASSA-PSS-SHA256", "1.2.840.113549.1.1.10"},
    {27, "RSASSA-PSS-SHA384", "1.2.840.113549.1.1.10"},
    {28, "RSASSA-PSS-SHA512", "1.2.840.113549.1.1.10"},
    {29, "RSASSA-PSS-SHAKE128", "1.3.6.1.5.5.7.6.30"},
    {30, "RSASSA-PSS-SHAKE256", "1.3.6.1.5.5.7.6.31"},
    {45, "sm2-with-sm3", "1.2.156.10197.1.501"},
};

static std::unordered_map<std::string, int> kNameToC509_Int_Signature = []
{
    std::unordered_map<std::string, int> m;
    for (const auto &e : kC509SignatureTable)
        m.emplace(e.name, e.value);
    return m;
}();

static std::unordered_map<std::string, int> kNameToC509_Int_PublicKey = []
{
    std::unordered_map<std::string, int> m;
    for (const auto &e : kC509PublicKeyTable)
        m.emplace(e.name, e.value);
    return m;
}();

static std::unordered_map<int, std::string> kC509_Int_ToOID = []
{
    std::unordered_map<int, std::string> m;
    for (const auto &e : kC509SignatureTable)
        m.emplace(e.value, e.oid);
    for (const auto &e : kC509PublicKeyTable)
        m.emplace(e.value, e.oid);
    return m;
}();

static std::unordered_map<std::string, int> kOID_To_C509_Int = []
{
    std::unordered_map<std::string, int> m;
    for (const auto &e : kC509SignatureTable)
        m.emplace(e.oid, e.value);
    for (const auto &e : kC509PublicKeyTable)
        m.emplace(e.oid, e.value);
    return m;
}();

static bool encode_oid(const std::string &oid_str, C509::AlgorithmIdentifier &identifier)
{
    std::vector<uint32_t> subids;
    size_t start = 0, end;
    while ((end = oid_str.find('.', start)) != std::string::npos)
    {
        subids.push_back(static_cast<uint32_t>(std::stoul(oid_str.substr(start, end - start))));
        start = end + 1;
    }
    subids.push_back(static_cast<uint32_t>(std::stoul(oid_str.substr(start))));
    identifier.type = C509::AlgorithmIdentifier::Type::OID;
    identifier.oid_algorithm_identifier.algorithm_identifier.subids.copy(subids.data(), subids.size());
    identifier.oid_algorithm_identifier.parameters.reset();
    return true;
}

static bool encode_int(int c509_value, C509::AlgorithmIdentifier &identifier)
{
    identifier.type = C509::AlgorithmIdentifier::Type::Int;
    identifier.int_algorithm_identifier = static_cast<uint8_t>(c509_value);
    return true;
}

bool map_alg_to_id(const std::string &algorithm, C509::AlgorithmIdentifier &identifier)
{
    if (auto it = kNameToOID_Signature.find(algorithm); it != kNameToOID_Signature.end())
        return encode_oid(it->second, identifier);
    if (auto it = kNameToOID_KEM.find(algorithm); it != kNameToOID_KEM.end())
        return encode_oid(it->second, identifier);

    if (auto it = kNameToC509_Int_Signature.find(algorithm); it != kNameToC509_Int_Signature.end())
        return encode_int(it->second, identifier);

    if (auto it = kNameToC509_Int_PublicKey.find(algorithm); it != kNameToC509_Int_PublicKey.end())
        return encode_int(it->second, identifier);

    bool dotted = !algorithm.empty() && std::all_of(algorithm.begin(), algorithm.end(), [](unsigned char c)
                                                    { return (c >= '0' && c <= '9') || c == '.'; });
    if (dotted)
        return encode_oid(algorithm, identifier);

    return false;
}

bool map_id_to_alg(std::string &algorithm, const C509::AlgorithmIdentifier &identifier)
{
    if (identifier.type == C509::AlgorithmIdentifier::Type::Int)
    {
        int v = static_cast<int>(identifier.int_algorithm_identifier);
        if (auto it = kC509_Int_ToOID.find(v); it != kC509_Int_ToOID.end())
        {
            algorithm = it->second;
            return true;
        }
        return false;
    }

    if (identifier.type != C509::AlgorithmIdentifier::Type::OID)
        return false;

    const auto &oid = identifier.oid_algorithm_identifier.algorithm_identifier;
    std::ostringstream oss;
    for (size_t i = 0; i < oid.subids.size(); ++i)
    {
        if (i > 0)
            oss << ".";
        oss << oid.subids[i];
    }
    const std::string dotted = oss.str();

    for (const auto &p : kNameToOID_Signature)
    {
        if (p.second == dotted)
        {
            algorithm = p.first;
            return true;
        }
    }
    for (const auto &p : kNameToOID_KEM)
    {
        if (p.second == dotted)
        {
            algorithm = p.first;
            return true;
        }
    }

    if (auto it = kOID_To_C509_Int.find(dotted); it != kOID_To_C509_Int.end())
    {
        algorithm = dotted;
        return true;
    }

    return false;
}
