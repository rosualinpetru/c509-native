#include <iostream>

#include "c509_core/csr.hpp"
#include "c509_core/algid_mapper.hpp"

#include "c509_crypto/crypto.hpp"
#include "c509_types/types.hpp"
#include "c509_codec/codec.hpp"

#define MAX_BUFFER_SIZE 4096

namespace C509::CSR {
    // TODO: for now, the CSR generation will only consider cases when the signature is generated with the same key pair

    bool generate_csr(
        const std::string &algorithm,
        const std::string &country,
        const std::string &state,
        const std::string &locality,
        const std::string &org,
        const std::string &orgUnit,
        const std::string &commonName,
        const std::string &emailAddress,
        const std::optional<std::string> &challengePassword,

        uint8_t *csr_out,
        size_t &csr_out_size,
        uint8_t *private_key_out,
        size_t &private_key_out_size) {
        OSSL_LIB_CTX *oqs_provider_ctx = load_oqs_provider();
        if (!oqs_provider_ctx) {
            std::cerr << "Failed to load OQS provider.\n";
            return false;
        }

        EVP_PKEY_CTX *pkey_ctx = EVP_PKEY_CTX_new_from_name(oqs_provider_ctx, algorithm.c_str(), OQSPROV_PROPQ);
        if (!pkey_ctx) {
            std::cerr << "Failed to create EVP_PKEY_CTX for algorithm " << algorithm << ".\n";
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (EVP_PKEY_keygen_init(pkey_ctx) <= 0) {
            std::cerr << "Failed to initialize key generation.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        EVP_PKEY *key = nullptr;
        if (EVP_PKEY_generate(pkey_ctx, &key) <= 0) {
            std::cerr << "Failed to generate composite key.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        C509CertificateRequest request{};

        if (challengePassword.has_value() && challengePassword.value().size() < MAX_CHALLENGE_PASSWORD_LEN) {
            request.challengePassword.set_has();
            request.challengePassword.get().type = ChallengePassword::Type::TSTR;
            // TODO: Additional checks should be made for BSTR
            request.challengePassword.get().bytes.copy(
                reinterpret_cast<const unsigned char *>(challengePassword.value().data()),
                challengePassword.value().size());
        } else
            request.challengePassword.reset();

        auto &tbs = request.tbsCertificateRequest;
        tbs.c509CertificateRequestType = 0;

        if (!algid_mapper(algorithm, tbs.subjectSignatureAlgorithm) || !algid_mapper(
                algorithm, tbs.subjectPublicKeyAlgorithm)) {
            std::cerr << "Failed to map algorithm to identifier\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        tbs.extensionsRequest.type = Extensions::Type::List;
        *tbs.extensionsRequest.extensions.len_p() = 0;

        if (EVP_PKEY_get_raw_public_key(key, tbs.subjectPublicKey.bytes.data_p(), tbs.subjectPublicKey.bytes.len_p()) <=
            0 && tbs.subjectPublicKey.bytes.size() >= MAX_PK_BYTES) {
            std::cerr << "Failed to extract public key - might not fit buffer.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        tbs.subject.type = Name::Type::Attributes;
        tbs.subject.attributes[0].type = Attribute::Type::Int;
        tbs.subject.attributes[0].intAttribute.attributeType = 0;
        tbs.subject.attributes[0].intAttribute.attributeValue.copy(
            reinterpret_cast<const unsigned char *>(emailAddress.c_str()), emailAddress.length());

        tbs.subject.attributes[1].type = Attribute::Type::Int;
        tbs.subject.attributes[1].intAttribute.attributeType = 1;
        tbs.subject.attributes[1].intAttribute.attributeValue.copy(
            reinterpret_cast<const unsigned char *>(commonName.c_str()), commonName.length());

        tbs.subject.attributes[2].type = Attribute::Type::Int;
        tbs.subject.attributes[2].intAttribute.attributeType = 4;
        tbs.subject.attributes[2].intAttribute.attributeValue.copy(
            reinterpret_cast<const unsigned char *>(country.c_str()), country.length());

        tbs.subject.attributes[3].type = Attribute::Type::Int;
        tbs.subject.attributes[3].intAttribute.attributeType = 5;
        tbs.subject.attributes[3].intAttribute.attributeValue.copy(
            reinterpret_cast<const unsigned char *>(locality.c_str()), locality.length());

        tbs.subject.attributes[4].type = Attribute::Type::Int;
        tbs.subject.attributes[4].intAttribute.attributeType = 6;
        tbs.subject.attributes[4].intAttribute.attributeValue.copy(
            reinterpret_cast<const unsigned char *>(state.c_str()), state.length());

        tbs.subject.attributes[5].type = Attribute::Type::Int;
        tbs.subject.attributes[5].intAttribute.attributeType = 8;
        tbs.subject.attributes[5].intAttribute.attributeValue.copy(reinterpret_cast<const unsigned char *>(org.c_str()),
                                                                   org.length());

        tbs.subject.attributes[6].type = Attribute::Type::Int;
        tbs.subject.attributes[6].intAttribute.attributeType = 9;
        tbs.subject.attributes[6].intAttribute.attributeValue.copy(
            reinterpret_cast<const unsigned char *>(orgUnit.c_str()), orgUnit.length());


        uint8_t buffer[MAX_BUFFER_SIZE];
        size_t buffer_size;
        if (encode(buffer, MAX_BUFFER_SIZE, &tbs, &buffer_size) != 0) {
            std::cerr << "Failed to encode TBSCertificateRequest.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (EVP_PKEY_sign_init(pkey_ctx) <= 0) {
            std::cerr << "Error: EVP_PKEY_sign_init() failed.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            return false;
        }

        if (EVP_PKEY_sign(pkey_ctx, request.subjectSignatureValue.bytes.data_p(),
                          request.subjectSignatureValue.bytes.len_p(), buffer,
                          buffer_size) <= 0 || request.subjectSignatureValue.bytes.size() > MAX_SIG_BYTES) {
            std::cerr << "Failed to sign TBSCertificateRequest.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (encode(csr_out, csr_out_size, &request, &csr_out_size) != 0) {
            std::cerr << "Failed to encode C509CertificateRequest.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        C509PrivateKey private_key{};

        if (!algid_mapper(algorithm, private_key.subjectPrivateKeyAlgorithm)) {
            std::cerr << "Failed to map algorithm to identifier\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (EVP_PKEY_get_raw_private_key(key, private_key.subjectPrivateKey.data_p(),
                                         private_key.subjectPrivateKey.len_p()) <= 0 && private_key.subjectPrivateKey.
            size() >=
            MAX_PRIV_KEY_BYTES) {
            std::cerr << "Failed to extract private key - might not fit buffer.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        if (encode(private_key_out, private_key_out_size, &private_key, &private_key_out_size) != 0) {
            std::cerr << "Failed to encode C509CertificateRequest.\n";
            EVP_PKEY_CTX_free(pkey_ctx);
            OSSL_LIB_CTX_free(oqs_provider_ctx);
            return false;
        }

        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(pkey_ctx);
        OSSL_LIB_CTX_free(oqs_provider_ctx);

        return true;
    }
}
