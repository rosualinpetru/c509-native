#ifndef C509_REGISTRY_H
#define C509_REGISTRY_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

// TODO: Should be either OID or int based on registry, but int extensions are not implemented
static const std::unordered_map<std::string, std::vector<uint32_t> > supported_cert_extensions = {
    {"subjectKeyIdentifier", {2, 5, 29, 14}},
    {"keyUsage", {2, 5, 29, 15}},
    {"subjectAltName", {2, 5, 29, 17}},
    {"basicConstraints", {2, 5, 29, 19}},
    {"cRLDistributionPoints", {2, 5, 29, 31}},
    {"certificatePolicies", {2, 5, 29, 32}},
    {"authorityKeyIdentifier", {2, 5, 29, 35}},
    {"extKeyUsage", {2, 5, 29, 37}},
    {"authorityInfoAccess", {1, 3, 6, 1, 5, 5, 7, 1, 1}},
    {"SignedCertificateTimestamps", {1, 3, 6, 1, 4, 1, 11129, 2, 4, 2}},
    {"subjectDirectoryAttributes", {2, 5, 29, 9}},
    {"issuerAltName", {2, 5, 29, 18}},
    {"nameConstraints", {2, 5, 29, 30}},
    {"policyMappings", {2, 5, 29, 33}},
    {"policyConstraints", {2, 5, 29, 36}},
    {"freshestCRL", {2, 5, 29, 46}},
    {"inhibitAnyPolicy", {2, 5, 29, 54}},
    {"subjectInfoAccess", {1, 3, 6, 1, 5, 5, 7, 1, 11}},
    {"id-pe-ipAddrBlocks", {1, 3, 6, 1, 5, 5, 7, 1, 7}},
    {"id-pe-autonomousSysIds", {1, 3, 6, 1, 5, 5, 7, 1, 8}},
    {"id-pe-ipAddrBlocks-v2", {1, 3, 6, 1, 5, 5, 7, 1, 28}},
    {"id-pe-autonomousSysIds-v2", {1, 3, 6, 1, 5, 5, 7, 1, 29}},
    {"id-pe-biometricInfo", {1, 3, 6, 1, 5, 5, 7, 1, 2}},
    {"PrecertificateSigningCertificate", {1, 3, 6, 1, 4, 1, 11129, 2, 4, 4}},
    {"id-pkix-ocsp-nocheck", {1, 3, 6, 1, 5, 5, 7, 48, 1, 5}},
    {"id-pe-qcStatements", {1, 3, 6, 1, 5, 5, 7, 1, 3}},
    {"smimeCapabilities", {1, 2, 840, 113549, 1, 9, 15}},
    {"id-pe-tlsfeature", {1, 3, 6, 1, 5, 5, 7, 1, 24}},
    {"challengePassword", {1, 2, 840, 113549, 1, 9, 7}}
};

// https://www.ietf.org/archive/id/draft-ietf-cose-cbor-encoded-cert-13.html#section-9.3-2
static const std::unordered_map<std::string, int> attribute_registry = {
    {"emailaddress", 0}, {"e-mailaddress", 0},
    {"commonname", 1}, {"cn", 1},
    {"surname", 2}, {"sn", 2},
    {"serialnumber", 3},
    {"countryname", 4}, {"c", 4},
    {"localityname", 5}, {"locality", 5}, {"l", 5},
    {"stateorprovincename", 6}, {"st", 6},
    {"streetaddress", 7}, {"street", 7},
    {"organizationname", 8}, {"o", 8},
    {"organizationalunitname", 9}, {"ou", 9},
    {"title", 10},
    {"businesscategory", 11},
    {"postalcode", 12},
    {"givenname", 13},
    {"initials", 14},
    {"generationqualifier", 15},
    {"dnqualifier", 16},
    {"pseudonym", 17},
    {"organizationidentifier", 18},
    {"jurisdictionofincorporationlocalityname", 19},
    {"jurisdictionofincorporationstateorprovincename", 20},
    {"jurisdictionofincorporationcountryname", 21},
    {"domaincomponent", 22}, {"dc", 22},
    {"postaladdress", 24},
    {"name", 25},
    {"telephonenumber", 26},
    {"dmdname", 27},
    {"uid", 28}, {"userid", 28},
    {"unstructuredname", 29},
    {"unstructuredaddress", 30}
};


#endif // C509_REGISTRY_H
