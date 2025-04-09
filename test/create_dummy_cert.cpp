#include <c509_core/c509.hpp>
#include <c509_crypto/crypto.hpp>

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <string>
#include <iostream>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include "test_helper.cpp"

using namespace C509;

#define ROOT_SIG "mldsa44"
#define CERT_PK "mldsa44"

namespace fs = std::filesystem;

EVP_PKEY *generate_public_key(OSSL_LIB_CTX *oqs_provider_ctx, const std::string &algorithm);

X509 *create_root_cert(EVP_PKEY *key);

X509 *create_satellite_cert(EVP_PKEY *key, X509 *issuer_cert, EVP_PKEY *issuer_key);

C509Certificate *create_root_c509(EVP_PKEY *key);

C509Certificate *create_satellite_c509(EVP_PKEY *key, C509Certificate *issuer_cert, EVP_PKEY *issuer_key);

bool write_cert_to_file(X509 *cert, const std::string &path);

bool write_c509_to_file(C509Certificate *cert, const std::string &path);

TEST_CASE("Gen Test Certificates") {
    OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();

    auto root_pk = generate_public_key(oqs_provider_ctx, ROOT_SIG);
    auto sat_pk = generate_public_key(oqs_provider_ctx, CERT_PK);

    auto root_cert = create_root_cert(root_pk);
    auto sat_cert = create_satellite_cert(sat_pk, root_cert, root_pk);

    auto root_c509 = create_root_c509(root_pk);

    std::string folder = std::string("exports/root-") + ROOT_SIG + "-sat-" + CERT_PK;
    fs::create_directories(folder);

    write_cert_to_file(root_cert, folder + "/root.x509.txt");
    write_cert_to_file(sat_cert, folder + "/sat.x509.txt");

    write_c509_to_file(root_c509, folder + "/root.c509.txt");

    // Cleanup
    EVP_PKEY_free(root_pk);
    EVP_PKEY_free(sat_pk);
    X509_free(root_cert);
    X509_free(sat_cert);
    OSSL_LIB_CTX_free(oqs_provider_ctx);
}

EVP_PKEY *generate_public_key(OSSL_LIB_CTX *oqs_provider_ctx, const std::string &algorithm) {
    EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm.c_str(), OQSPROV_PROPQ);
    EVP_PKEY_keygen_init(pkey_ctx);
    EVP_PKEY *key = nullptr;
    EVP_PKEY_generate(pkey_ctx, &key);
    return key;
}

// Build ESA Root CA certificate
X509 *create_root_cert(EVP_PKEY *key) {
    X509 *cert = X509_new();
    X509_set_version(cert, 2);
    ASN1_INTEGER_set(X509_get_serialNumber(cert), 1);
    X509_gmtime_adj(X509_get_notBefore(cert), 0);
    X509_gmtime_adj(X509_get_notAfter(cert), 31536000L);

    // Subject & Issuer
    X509_NAME *name = X509_get_subject_name(cert);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *) "ESA Root CA", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (unsigned char *) "ESA", -1, -1, 0);

    X509_set_issuer_name(cert, name);

    // PK
    X509_set_pubkey(cert, key);

    // Extensions
    X509V3_CTX ctx;
    X509V3_set_ctx(&ctx, cert, cert, nullptr, nullptr, 0);

    X509_EXTENSION *ext;
    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_basic_constraints, "critical,CA:TRUE,pathlen:3");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_key_usage, "critical,keyCertSign,cRLSign");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_subject_key_identifier, "hash");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    X509_sign(cert, key, EVP_sha256());
    return cert;
}

C509Certificate *create_root_c509(EVP_PKEY *key) {
    auto *cert = new C509Certificate();

    auto &tbs = cert->tbs_certificate;

    tbs.c509_certificate_type = 2;
    tbs.certificate_serial_number.bytes.copy(reinterpret_cast<const unsigned char *>("1"), 1);
    tbs.validity_not_before.epoch_seconds = 0;
    tbs.validity_not_after.get().epoch_seconds = 31536000L;
    tbs.validity_not_after.set_has();

    // Subject & Issuer
    tbs.subject.type = Name::Type::Attributes;
    *tbs.subject.attributes.len_p() = 2;

    tbs.subject.attributes[0].type = Attribute::Type::Int;
    tbs.subject.attributes[0].attribute_type.integer = 1;
    tbs.subject.attributes[0].attribute_value.copy(reinterpret_cast<const unsigned char *>("ESA Root CA"),
                                                   strlen("ESA Root CA"));

    tbs.subject.attributes[1].type = Attribute::Type::Int;
    tbs.subject.attributes[1].attribute_type.integer = 8;
    tbs.subject.attributes[1].attribute_value.copy(reinterpret_cast<const unsigned char *>("ESA"), strlen("ESA"));

    tbs.issuer.reset();

    // TODO: PK
    if (!map_alg_to_id(ROOT_SIG, tbs.issuer_signature_algorithm) || !map_alg_to_id(
            ROOT_SIG, tbs.subject_public_key_algorithm))
        exit(1);


    *tbs.subject_public_key.bytes.len_p() = tbs.subject_public_key.bytes.capacity();
    if (EVP_PKEY_get_raw_public_key(key, tbs.subject_public_key.bytes.data_p(),
                                    tbs.subject_public_key.bytes.len_p()) <= 0)
        exit(2);


    // Extensions
    tbs.extensions.type = Extensions::Type::List;
    *tbs.extensions.extensions.len_p() = 3;
    tbs.extensions.extensions[0].type = Extension::Type::Int;
    tbs.extensions.extensions[0].int_extension.extension_id = -4;
    auto *basic_constraints = new BasicConstraints();
    basic_constraints->value = 3;
    tbs.extensions.extensions[0].int_extension.extension = basic_constraints;

    tbs.extensions.extensions[1].type = Extension::Type::Int;
    tbs.extensions.extensions[1].int_extension.extension_id = -2;
    auto *key_usage = new KeyUsage({KeyUsage::UsageBit::keyCertSign, KeyUsage::UsageBit::cRLSign});
    tbs.extensions.extensions[1].int_extension.extension = key_usage;

    tbs.extensions.extensions[2].type = Extension::Type::Int;
    tbs.extensions.extensions[2].int_extension.extension_id = 1;
    uint8_t pk_cbor[MAX_BUFFER_SIZE] = {};
    size_t pk_cbor_size = sizeof(pk_cbor);
    if (cbor_encode(pk_cbor, MAX_BUFFER_SIZE, &tbs.subject_public_key, &pk_cbor_size) != 0)
        exit(3);

    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256(pk_cbor, pk_cbor_size, hash);
    auto *ski = new SubjectKeyIdentifier();
    ski->value.copy(hash, 20);
    tbs.extensions.extensions[2].int_extension.extension = ski;

    // Sign the TBS certificate
    EVP_PKEY_CTX *sign_ctx = EVP_PKEY_CTX_new(key, nullptr);
    if (!sign_ctx || EVP_PKEY_sign_init(sign_ctx) <= 0) {
        exit(4);
    }

    uint8_t tbs_buffer[MAX_BUFFER_SIZE];
    size_t tbs_buffer_size;
    if (cbor_encode(tbs_buffer, MAX_BUFFER_SIZE, &cert->tbs_certificate, &tbs_buffer_size) != 0) {
        exit(5);
    }

    *cert->signature_value.bytes.len_p() = cert->signature_value.bytes.capacity();
    if (EVP_PKEY_sign(sign_ctx, cert->signature_value.bytes.data_p(),
                      cert->signature_value.bytes.len_p(), tbs_buffer, tbs_buffer_size) <= 0) {
        exit(6);
    }

    return cert;
}

X509 *create_satellite_cert(EVP_PKEY *key, X509 *issuer_cert, EVP_PKEY *issuer_key) {
    X509 *cert = X509_new();
    X509_set_version(cert, 2);
    ASN1_INTEGER_set(X509_get_serialNumber(cert), 2);
    X509_gmtime_adj(X509_get_notBefore(cert), 0);
    X509_gmtime_adj(X509_get_notAfter(cert), 31536000L);

    X509_NAME *name = X509_get_subject_name(cert);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *) "CryoSat-2", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "OU", MBSTRING_ASC, (unsigned char *) "Satellite Ops", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (unsigned char *) "ESA", -1, -1, 0);

    X509_set_issuer_name(cert, X509_get_subject_name(issuer_cert));

    X509_set_pubkey(cert, key);

    X509V3_CTX ctx;
    X509V3_set_ctx(&ctx, issuer_cert, cert, nullptr, nullptr, 0);

    X509_EXTENSION *ext;
    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_basic_constraints, "critical,CA:FALSE");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_key_usage, "critical,digitalSignature");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_subject_key_identifier, "hash");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_authority_key_identifier, "keyid:always");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_crl_distribution_points, "URI:http://ca.esa.int/gs-ca.crl");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_freshest_crl, "URI:http://ca.esa.int/gs-ca-delta.crl");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    ext = X509V3_EXT_conf_nid(nullptr, &ctx, NID_info_access,
                              "OCSP;URI:http://ocsp.esa.int/gs-ca,caIssuers;URI:http://ca.esa.int/gs-ca.pem");
    X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);

    X509_sign(cert, issuer_key, EVP_sha256());
    return cert;
}


C509Certificate *create_satellite_c509(EVP_PKEY *key, C509Certificate *issuer_cert, EVP_PKEY *issuer_key) {
}

bool write_cert_to_file(X509 *cert, const std::string &path) {
    int len = i2d_X509(cert, nullptr);
    if (len <= 0) return false;

    std::vector<unsigned char> der(len);
    unsigned char *p = der.data();
    i2d_X509(cert, &p);

    FILE *f = fopen(path.c_str(), "w");
    if (!f) return false;

    for (int i = 0; i < len; ++i) {
        fprintf(f, "%02X", der[i]);
        if ((i + 1) % 32 == 0) fprintf(f, "\n"); // proper newline
    }
    if (len % 32 != 0) fprintf(f, "\n"); // ensure newline at end
    fclose(f);
    return true;
}

bool write_c509_to_file(C509Certificate *cert, const std::string &path) {
    uint8_t cert_out[MAX_BUFFER_SIZE] = {};
    size_t cert_out_size = sizeof(cert_out);
    if (cbor_encode(cert_out, MAX_BUFFER_SIZE, cert, &cert_out_size) != 0)
        exit(3);

    FILE *f = fopen(path.c_str(), "w");
    if (!f) return false;

    for (int i = 0; i < cert_out_size; ++i) {
        fprintf(f, "%02X", cert_out[i]);
        if ((i + 1) % 32 == 0) fprintf(f, "\n"); // proper newline
    }
    if (cert_out_size % 32 != 0) fprintf(f, "\n"); // ensure newline at end
    fclose(f);
    return true;
}
