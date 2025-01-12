/*
 * Generated using zcbor version 0.9.99-2b837d1
 * https://github.com/NordicSemiconductor/zcbor
 * at: 2025-01-12 19:18:44
 * Generated with a --default-max-qty of 1024
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <zcbor_encode.h>
#include <zcbor_print.h>

#include <c509_encode.hpp>

#if DEFAULT_MAX_QTY != 1024
#error "The type file was generated with a different default_max_qty than this file"
#endif

#define log_result(state, result, func) do { \
	if (!result) { \
		zcbor_trace_file(state); \
		zcbor_log("%s error: %s\r\n", func, zcbor_error_str(zcbor_peek_error(state))); \
	} else { \
		zcbor_log("%s success\r\n", func); \
	} \
} while(0)

static bool encode_biguint(zcbor_state_t *state, const struct zcbor_string *input);
static bool encode_oid(zcbor_state_t *state, const struct zcbor_string *input);
static bool encode_AlgorithmIdentifier(zcbor_state_t *state, const struct AlgorithmIdentifier_r *input);
static bool encode_Attribute(zcbor_state_t *state, const struct Attribute_r *input);
static bool encode_Name(zcbor_state_t *state, const struct Name_r *input);
static bool encode_number(zcbor_state_t *state, const struct number_r *input);
static bool encode_time(zcbor_state_t *state, const struct number_r *input);
static bool encode_Extension(zcbor_state_t *state, const struct Extension_r *input);
static bool encode_Extensions(zcbor_state_t *state, const struct Extensions_r *input);
static bool encode_TBSCertificate(zcbor_state_t *state, const struct TBSCertificate *input);
static bool encode_C509Certificate(zcbor_state_t *state, const struct C509Certificate *input);
static bool encode_repeated_PolicyMappings_issuerDomainPolicy_l(zcbor_state_t *state, const struct PolicyMappings_issuerDomainPolicy_l *input);
static bool encode_PolicyMappings(zcbor_state_t *state, const struct PolicyMappings *input);
static bool encode_PolicyConstraints(zcbor_state_t *state, const struct PolicyConstraints *input);
static bool encode_KeyPurposeId(zcbor_state_t *state, const struct KeyPurposeId_r *input);
static bool encode_ExtKeyUsageSyntax(zcbor_state_t *state, const struct ExtKeyUsageSyntax_r *input);
static bool encode_GeneralName(zcbor_state_t *state, const struct GeneralName *input);
static bool encode_GeneralNames(zcbor_state_t *state, const struct GeneralNames *input);
static bool encode_SubjectAltName(zcbor_state_t *state, const struct SubjectAltName_r *input);
static bool encode_IssuerAltName(zcbor_state_t *state, const struct IssuerAltName_r *input);
static bool encode_DistributionPointName(zcbor_state_t *state, const struct DistributionPointName_r *input);
static bool encode_CRLDistributionPoints(zcbor_state_t *state, const struct CRLDistributionPoints *input);
static bool encode_uri(zcbor_state_t *state, const struct zcbor_string *input);
static bool encode_AccessDescription(zcbor_state_t *state, const struct AccessDescription *input);
static bool encode_AuthorityInfoAccessSyntax(zcbor_state_t *state, const struct AuthorityInfoAccessSyntax *input);
static bool encode_KeyIdentifierArray(zcbor_state_t *state, const struct KeyIdentifierArray *input);
static bool encode_AuthorityKeyIdentifier(zcbor_state_t *state, const struct AuthorityKeyIdentifier_r *input);
static bool encode_PolicyIdentifier(zcbor_state_t *state, const struct PolicyIdentifier_r *input);
static bool encode_PolicyQualifierInfo(zcbor_state_t *state, const struct PolicyQualifierInfo *input);
static bool encode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l(zcbor_state_t *state, const struct PolicyIdentifier_m_l_PolicyQualifierInfo_m_l *input);
static bool encode_repeated_CertificatePolicies_PolicyIdentifier_m_l(zcbor_state_t *state, const struct CertificatePolicies_PolicyIdentifier_m_l *input);
static bool encode_CertificatePolicies(zcbor_state_t *state, const struct CertificatePolicies *input);
static bool encode_GeneralSubtrees(zcbor_state_t *state, const struct GeneralSubtrees *input);
static bool encode_NameConstraints(zcbor_state_t *state, const struct NameConstraints *input);
static bool encode_Attributes(zcbor_state_t *state, const struct Attributes_r *input);
static bool encode_SubjectDirectoryAttributes(zcbor_state_t *state, const struct SubjectDirectoryAttributes *input);
static bool encode_ASIdOrRange(zcbor_state_t *state, const struct ASIdOrRange_r *input);
static bool encode_ASIdentifiers(zcbor_state_t *state, const struct ASIdentifiers_r *input);
static bool encode_AddressPrefix(zcbor_state_t *state, const struct AddressPrefix *input);
static bool encode_AddressRange(zcbor_state_t *state, const struct AddressRange *input);
static bool encode_IPAddressOrRange(zcbor_state_t *state, const struct IPAddressOrRange_r *input);
static bool encode_IPAddressChoice(zcbor_state_t *state, const struct IPAddressChoice_r *input);
static bool encode_IPAddressFamily(zcbor_state_t *state, const struct IPAddressFamily *input);
static bool encode_IPAddrBlocks(zcbor_state_t *state, const struct IPAddrBlocks *input);
static bool encode_SignedCertificateTimestamp(zcbor_state_t *state, const struct SignedCertificateTimestamp *input);
static bool encode_SignedCertificateTimestamps(zcbor_state_t *state, const struct SignedCertificateTimestamps *input);
static bool encode_All(zcbor_state_t *state, const struct All *input);


static bool encode_biguint(
		zcbor_state_t *state, const struct zcbor_string *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = ((zcbor_tag_put(state, 2)
	&& (zcbor_bstr_encode(state, (&(*input))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_oid(
		zcbor_state_t *state, const struct zcbor_string *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = ((zcbor_tag_put(state, 111)
	&& (zcbor_bstr_encode(state, (&(*input))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_AlgorithmIdentifier(
		zcbor_state_t *state, const struct AlgorithmIdentifier_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).AlgorithmIdentifier_choice == AlgorithmIdentifier_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: (((*input).AlgorithmIdentifier_choice == AlgorithmIdentifier_oid_m_c) ? ((encode_oid(state, (&(*input).oid_m))))
	: (((*input).AlgorithmIdentifier_choice == AlgorithmIdentifier_algorithm_l_c) ? ((zcbor_list_start_encode(state, 2) && ((((encode_oid(state, (&(*input).algorithm))))
	&& ((zcbor_bstr_encode(state, (&(*input).parameters))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2)))
	: false)))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_Attribute(
		zcbor_state_t *state, const struct Attribute_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).Attribute_choice == Attribute_attributeTypeInt_l_c) ? ((((zcbor_int32_encode(state, (&(*input).attributeTypeInt))))
	&& ((zcbor_tstr_encode(state, (&(*input).attributeValueText))))))
	: (((*input).Attribute_choice == Attribute_attributeTypeOID_l_c) ? ((((encode_oid(state, (&(*input).attributeTypeOID))))
	&& ((zcbor_bstr_encode(state, (&(*input).attributeValueBytes))))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_Name(
		zcbor_state_t *state, const struct Name_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).Name_choice == Name_Attribute_m_l_c) ? ((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(0, 1024, &(*input).Attribute_m_count, (zcbor_encoder_t *)encode_Attribute, state, (*&(*input).Attribute_m), sizeof(struct Attribute_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048)))
	: (((*input).Name_choice == Name_text_m_c) ? ((zcbor_tstr_encode(state, (&(*input).text_m))))
	: (((*input).Name_choice == Name_bytes_m_c) ? ((zcbor_bstr_encode(state, (&(*input).bytes_m))))
	: false)))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_number(
		zcbor_state_t *state, const struct number_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).number_choice == number_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: (((*input).number_choice == number_float_c) ? ((zcbor_float64_encode(state, (&(*input).Float))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_time(
		zcbor_state_t *state, const struct number_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = ((zcbor_tag_put(state, 1)
	&& (encode_number(state, (&(*input))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_Extension(
		zcbor_state_t *state, const struct Extension_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).Extension_choice == Extension_extensionIDInt_l_c) ? ((((zcbor_int32_encode(state, (&(*input).extensionIDInt))))
	&& ((zcbor_nil_put(state, NULL)))))
	: (((*input).Extension_choice == Extension_extensionIDOID_l_c) ? ((((encode_oid(state, (&(*input).extensionIDOID))))
	&& (!(*input).critical_present || zcbor_bool_put(state, (true)))
	&& ((zcbor_bstr_encode(state, (&(*input).extensionValueBytes))))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_Extensions(
		zcbor_state_t *state, const struct Extensions_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).Extensions_choice == Extensions_Extension_m_l_c) ? ((zcbor_list_start_encode(state, 3072) && ((zcbor_multi_encode_minmax(0, 1024, &(*input).Extension_m_count, (zcbor_encoder_t *)encode_Extension, state, (*&(*input).Extension_m), sizeof(struct Extension_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 3072)))
	: (((*input).Extensions_choice == Extensions_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_TBSCertificate(
		zcbor_state_t *state, const struct TBSCertificate *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((zcbor_int32_encode(state, (&(*input).c509CertificateType))))
	&& ((encode_biguint(state, (&(*input).certificateSerialNumber))))
	&& ((encode_AlgorithmIdentifier(state, (&(*input).issuerSignatureAlgorithm))))
	&& ((((*input).issuer_choice == TBSCertificate_issuer_Name_m_c) ? ((encode_Name(state, (&(*input).Name_m))))
	: (((*input).issuer_choice == TBSCertificate_issuer_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false)))
	&& ((encode_time(state, (&(*input).validityNotBefore))))
	&& ((((*input).validityNotAfter_choice == TBSCertificate_validityNotAfter_time_m_c) ? ((encode_time(state, (&(*input).time_m))))
	: (((*input).validityNotAfter_choice == TBSCertificate_validityNotAfter_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false)))
	&& ((encode_Name(state, (&(*input).subject))))
	&& ((encode_AlgorithmIdentifier(state, (&(*input).subjectPublicKeyAlgorithm))))
	&& ((zcbor_nil_put(state, NULL)))
	&& ((encode_Extensions(state, (&(*input).extensions)))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_C509Certificate(
		zcbor_state_t *state, const struct C509Certificate *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 11) && ((((encode_TBSCertificate(state, (&(*input).TBSCertificate_m))))
	&& ((zcbor_nil_put(state, NULL)))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 11))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_repeated_PolicyMappings_issuerDomainPolicy_l(
		zcbor_state_t *state, const struct PolicyMappings_issuerDomainPolicy_l *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((encode_oid(state, (&(*input).issuerDomainPolicy))))
	&& ((encode_oid(state, (&(*input).subjectDomainPolicy)))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_PolicyMappings(
		zcbor_state_t *state, const struct PolicyMappings *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).issuerDomainPolicy_l_count, (zcbor_encoder_t *)encode_repeated_PolicyMappings_issuerDomainPolicy_l, state, (*&(*input).issuerDomainPolicy_l), sizeof(struct PolicyMappings_issuerDomainPolicy_l))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_PolicyConstraints(
		zcbor_state_t *state, const struct PolicyConstraints *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2) && ((((((*input).requireExplicitPolicy_choice == PolicyConstraints_requireExplicitPolicy_uint_c) ? ((zcbor_uint32_encode(state, (&(*input).uint))))
	: (((*input).requireExplicitPolicy_choice == PolicyConstraints_requireExplicitPolicy_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false)))
	&& ((((*input).inhibitPolicyMapping_choice == PolicyConstraints_inhibitPolicyMapping_uint_c) ? ((zcbor_uint32_encode(state, (&(*input).uint))))
	: (((*input).inhibitPolicyMapping_choice == PolicyConstraints_inhibitPolicyMapping_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false)))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_KeyPurposeId(
		zcbor_state_t *state, const struct KeyPurposeId_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).KeyPurposeId_choice == KeyPurposeId_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: (((*input).KeyPurposeId_choice == KeyPurposeId_oid_m_c) ? ((encode_oid(state, (&(*input).oid_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_ExtKeyUsageSyntax(
		zcbor_state_t *state, const struct ExtKeyUsageSyntax_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).ExtKeyUsageSyntax_choice == ExtKeyUsageSyntax_KeyPurposeId_m_l_c) ? ((zcbor_list_start_encode(state, 1024) && ((zcbor_multi_encode_minmax(2, 1024, &(*input).KeyPurposeId_m_count, (zcbor_encoder_t *)encode_KeyPurposeId, state, (*&(*input).KeyPurposeId_m), sizeof(struct KeyPurposeId_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 1024)))
	: (((*input).ExtKeyUsageSyntax_choice == ExtKeyUsageSyntax_KeyPurposeId_m_c) ? ((encode_KeyPurposeId(state, (&(*input).KeyPurposeId_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_GeneralName(
		zcbor_state_t *state, const struct GeneralName *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((zcbor_int32_encode(state, (&(*input).GeneralNameType))))
	&& ((zcbor_nil_put(state, NULL))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_GeneralNames(
		zcbor_state_t *state, const struct GeneralNames *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).GeneralName_m_count, (zcbor_encoder_t *)encode_GeneralName, state, (*&(*input).GeneralName_m), sizeof(struct GeneralName))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_SubjectAltName(
		zcbor_state_t *state, const struct SubjectAltName_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).SubjectAltName_choice == SubjectAltName_GeneralNames_m_c) ? ((encode_GeneralNames(state, (&(*input).GeneralNames_m))))
	: (((*input).SubjectAltName_choice == SubjectAltName_text_m_c) ? ((zcbor_tstr_encode(state, (&(*input).text_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_IssuerAltName(
		zcbor_state_t *state, const struct IssuerAltName_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).IssuerAltName_choice == IssuerAltName_GeneralNames_m_c) ? ((encode_GeneralNames(state, (&(*input).GeneralNames_m))))
	: (((*input).IssuerAltName_choice == IssuerAltName_text_m_c) ? ((zcbor_tstr_encode(state, (&(*input).text_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_DistributionPointName(
		zcbor_state_t *state, const struct DistributionPointName_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).DistributionPointName_choice == DistributionPointName_text_m_l_c) ? ((zcbor_list_start_encode(state, 1024) && ((zcbor_multi_encode_minmax(2, 1024, &(*input).text_m_count, (zcbor_encoder_t *)zcbor_tstr_encode, state, (*&(*input).text_m), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 1024)))
	: (((*input).DistributionPointName_choice == DistributionPointName_text_m_c) ? ((zcbor_tstr_encode(state, (&(*input).text_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_CRLDistributionPoints(
		zcbor_state_t *state, const struct CRLDistributionPoints *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 1024) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).DistributionPointName_m_count, (zcbor_encoder_t *)encode_DistributionPointName, state, (*&(*input).DistributionPointName_m), sizeof(struct DistributionPointName_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 1024))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_uri(
		zcbor_state_t *state, const struct zcbor_string *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = ((zcbor_tag_put(state, 32)
	&& (zcbor_tstr_encode(state, (&(*input))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_AccessDescription(
		zcbor_state_t *state, const struct AccessDescription *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((((*input).accessMethod_choice == AccessDescription_accessMethod_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: (((*input).accessMethod_choice == AccessDescription_accessMethod_oid_m_c) ? ((encode_oid(state, (&(*input).oid_m))))
	: false)))
	&& (((encode_uri(state, (&(*input).uri_key))))
	&& (zcbor_tstr_encode(state, (&(*input).uri)))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_AuthorityInfoAccessSyntax(
		zcbor_state_t *state, const struct AuthorityInfoAccessSyntax *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).AccessDescription_m_count, (zcbor_encoder_t *)encode_AccessDescription, state, (*&(*input).AccessDescription_m), sizeof(struct AccessDescription))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_KeyIdentifierArray(
		zcbor_state_t *state, const struct KeyIdentifierArray *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 3) && ((((zcbor_bstr_encode(state, (&(*input).keyIdentifier))))
	&& ((encode_GeneralNames(state, (&(*input).authorityCertIssuer))))
	&& ((encode_biguint(state, (&(*input).authorityCertSerialNumber))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 3))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_AuthorityKeyIdentifier(
		zcbor_state_t *state, const struct AuthorityKeyIdentifier_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).AuthorityKeyIdentifier_choice == AuthorityKeyIdentifier_KeyIdentifierArray_m_c) ? ((encode_KeyIdentifierArray(state, (&(*input).KeyIdentifierArray_m))))
	: (((*input).AuthorityKeyIdentifier_choice == AuthorityKeyIdentifier_KeyIdentifier_m_c) ? ((zcbor_bstr_encode(state, (&(*input).KeyIdentifier_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_PolicyIdentifier(
		zcbor_state_t *state, const struct PolicyIdentifier_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).PolicyIdentifier_choice == PolicyIdentifier_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: (((*input).PolicyIdentifier_choice == PolicyIdentifier_oid_m_c) ? ((encode_oid(state, (&(*input).oid_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_PolicyQualifierInfo(
		zcbor_state_t *state, const struct PolicyQualifierInfo *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((((*input).policyQualifierId_choice == PolicyQualifierInfo_policyQualifierId_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
	: (((*input).policyQualifierId_choice == PolicyQualifierInfo_policyQualifierId_oid_m_c) ? ((encode_oid(state, (&(*input).oid_m))))
	: false)))
	&& ((zcbor_tstr_encode(state, (&(*input).qualifier)))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l(
		zcbor_state_t *state, const struct PolicyIdentifier_m_l_PolicyQualifierInfo_m_l *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).PolicyQualifierInfo_m_count, (zcbor_encoder_t *)encode_PolicyQualifierInfo, state, (*&(*input).PolicyQualifierInfo_m), sizeof(struct PolicyQualifierInfo))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_repeated_CertificatePolicies_PolicyIdentifier_m_l(
		zcbor_state_t *state, const struct CertificatePolicies_PolicyIdentifier_m_l *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((encode_PolicyIdentifier(state, (&(*input).PolicyIdentifier_m))))
	&& (!(*input).PolicyQualifierInfo_m_l_present || encode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l(state, (&(*input).PolicyQualifierInfo_m_l))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_CertificatePolicies(
		zcbor_state_t *state, const struct CertificatePolicies *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).PolicyIdentifier_m_l_count, (zcbor_encoder_t *)encode_repeated_CertificatePolicies_PolicyIdentifier_m_l, state, (*&(*input).PolicyIdentifier_m_l), sizeof(struct CertificatePolicies_PolicyIdentifier_m_l))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_GeneralSubtrees(
		zcbor_state_t *state, const struct GeneralSubtrees *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).GeneralName_m_count, (zcbor_encoder_t *)encode_GeneralName, state, (*&(*input).GeneralName_m), sizeof(struct GeneralName))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_NameConstraints(
		zcbor_state_t *state, const struct NameConstraints *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2) && ((((((*input).permittedSubtrees_choice == NameConstraints_permittedSubtrees_GeneralSubtrees_m_c) ? ((encode_GeneralSubtrees(state, (&(*input).GeneralSubtrees_m))))
	: (((*input).permittedSubtrees_choice == NameConstraints_permittedSubtrees_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false)))
	&& ((((*input).excludedSubtrees_choice == NameConstraints_excludedSubtrees_GeneralSubtrees_m_c) ? ((encode_GeneralSubtrees(state, (&(*input).GeneralSubtrees_m))))
	: (((*input).excludedSubtrees_choice == NameConstraints_excludedSubtrees_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false)))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_Attributes(
		zcbor_state_t *state, const struct Attributes_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).Attributes_choice == Attributes_attributeTypesInt_l_c) ? ((((zcbor_int32_encode(state, (&(*input).attributeTypesInt))))
	&& ((zcbor_list_start_encode(state, 1024) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).text_m_count, (zcbor_encoder_t *)zcbor_tstr_encode, state, (*&(*input).text_m), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 1024)))))
	: (((*input).Attributes_choice == Attributes_attributeTypesOID_l_c) ? ((((encode_oid(state, (&(*input).attributeTypesOID))))
	&& ((zcbor_list_start_encode(state, 1024) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).bytes_m_count, (zcbor_encoder_t *)zcbor_bstr_encode, state, (*&(*input).bytes_m), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 1024)))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_SubjectDirectoryAttributes(
		zcbor_state_t *state, const struct SubjectDirectoryAttributes *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).Attributes_m_count, (zcbor_encoder_t *)encode_Attributes, state, (*&(*input).Attributes_m), sizeof(struct Attributes_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_ASIdOrRange(
		zcbor_state_t *state, const struct ASIdOrRange_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).ASIdOrRange_choice == ASIdOrRange_uint_c) ? ((zcbor_uint32_encode(state, (&(*input).uint))))
	: (((*input).ASIdOrRange_choice == ASIdOrRange_min_l_c) ? ((zcbor_list_start_encode(state, 2) && ((((zcbor_uint32_encode(state, (&(*input).min))))
	&& ((zcbor_uint32_encode(state, (&(*input).max))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2)))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_ASIdentifiers(
		zcbor_state_t *state, const struct ASIdentifiers_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).ASIdentifiers_choice == ASIdentifiers_ASIdOrRange_m_l_c) ? ((zcbor_list_start_encode(state, 1024) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).ASIdOrRange_m_count, (zcbor_encoder_t *)encode_ASIdOrRange, state, (*&(*input).ASIdOrRange_m), sizeof(struct ASIdOrRange_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 1024)))
	: (((*input).ASIdentifiers_choice == ASIdentifiers_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_AddressPrefix(
		zcbor_state_t *state, const struct AddressPrefix *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((zcbor_bstr_encode(state, (&(*input).Address_m))))
	&& ((zcbor_uint32_encode(state, (&(*input).unusedBits)))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_AddressRange(
		zcbor_state_t *state, const struct AddressRange *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2) && ((((zcbor_bstr_encode(state, (&(*input).min))))
	&& ((zcbor_bstr_encode(state, (&(*input).max))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_IPAddressOrRange(
		zcbor_state_t *state, const struct IPAddressOrRange_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).IPAddressOrRange_choice == IPAddressOrRange_AddressPrefix_m_c) ? ((encode_AddressPrefix(state, (&(*input).AddressPrefix_m))))
	: (((*input).IPAddressOrRange_choice == IPAddressOrRange_AddressRange_m_c) ? ((encode_AddressRange(state, (&(*input).AddressRange_m))))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_IPAddressChoice(
		zcbor_state_t *state, const struct IPAddressChoice_r *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((*input).IPAddressChoice_choice == IPAddressChoice_IPAddressOrRange_m_l_c) ? ((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).IPAddressOrRange_m_count, (zcbor_encoder_t *)encode_IPAddressOrRange, state, (*&(*input).IPAddressOrRange_m), sizeof(struct IPAddressOrRange_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048)))
	: (((*input).IPAddressChoice_choice == IPAddressChoice_null_m_c) ? ((zcbor_nil_put(state, NULL)))
	: false))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_IPAddressFamily(
		zcbor_state_t *state, const struct IPAddressFamily *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((zcbor_uint32_encode(state, (&(*input).AFI))))
	&& ((encode_IPAddressChoice(state, (&(*input).IPAddressChoice_m)))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_IPAddrBlocks(
		zcbor_state_t *state, const struct IPAddrBlocks *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).IPAddressFamily_m_count, (zcbor_encoder_t *)encode_IPAddressFamily, state, (*&(*input).IPAddressFamily_m), sizeof(struct IPAddressFamily))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_SignedCertificateTimestamp(
		zcbor_state_t *state, const struct SignedCertificateTimestamp *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((((zcbor_bstr_encode(state, (&(*input).logID))))
	&& ((zcbor_int32_encode(state, (&(*input).timestamp))))
	&& ((encode_AlgorithmIdentifier(state, (&(*input).sigAlg))))
	&& ((zcbor_nil_put(state, NULL))))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_SignedCertificateTimestamps(
		zcbor_state_t *state, const struct SignedCertificateTimestamps *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_list_start_encode(state, 4096) && ((zcbor_multi_encode_minmax(1, 1024, &(*input).SignedCertificateTimestamp_m_count, (zcbor_encoder_t *)encode_SignedCertificateTimestamp, state, (*&(*input).SignedCertificateTimestamp_m), sizeof(struct SignedCertificateTimestamp))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 4096))));

	log_result(state, res, __func__);
	return res;
}

static bool encode_All(
		zcbor_state_t *state, const struct All *input)
{
	zcbor_log("%s\r\n", __func__);

	bool res = (((zcbor_map_start_encode(state, 67) && (((((encode_C509Certificate(state, (&(*input).C509Certificate_key))))
	&& (encode_C509Certificate(state, (&(*input).C509Certificate))))
	&& (((encode_TBSCertificate(state, (&(*input).TBSCertificate_key))))
	&& (encode_TBSCertificate(state, (&(*input).TBSCertificate))))
	&& (((encode_biguint(state, (&(*input).CertificateSerialNumber_key))))
	&& (encode_biguint(state, (&(*input).CertificateSerialNumber))))
	&& (((encode_Name(state, (&(*input).Name_key))))
	&& (encode_Name(state, (&(*input).Name))))
	&& (((encode_Attribute(state, (&(*input).Attribute_key))))
	&& (encode_Attribute(state, (&(*input).Attribute))))
	&& (((encode_AlgorithmIdentifier(state, (&(*input).AlgorithmIdentifier_key))))
	&& (encode_AlgorithmIdentifier(state, (&(*input).AlgorithmIdentifier))))
	&& (((encode_Extensions(state, (&(*input).Extensions_key))))
	&& (encode_Extensions(state, (&(*input).Extensions))))
	&& (((encode_Extension(state, (&(*input).Extension_key))))
	&& (encode_Extension(state, (&(*input).Extension))))
	&& (((zcbor_bstr_encode(state, (&(*input).KeyIdentifier_key))))
	&& (zcbor_bstr_encode(state, (&(*input).KeyIdentifier))))
	&& (((zcbor_bstr_encode(state, (&(*input).SubjectKeyIdentifier_key))))
	&& (zcbor_bstr_encode(state, (&(*input).SubjectKeyIdentifier))))
	&& (((zcbor_int32_encode(state, (&(*input).KeyUsage_key))))
	&& (zcbor_int32_encode(state, (&(*input).KeyUsage))))
	&& (((encode_PolicyMappings(state, (&(*input).PolicyMappings_key))))
	&& (encode_PolicyMappings(state, (&(*input).PolicyMappings))))
	&& (((zcbor_int32_encode(state, (&(*input).BasicConstraints_key))))
	&& (zcbor_int32_encode(state, (&(*input).BasicConstraints))))
	&& (((encode_PolicyConstraints(state, (&(*input).PolicyConstraints_key))))
	&& (encode_PolicyConstraints(state, (&(*input).PolicyConstraints))))
	&& (((encode_KeyPurposeId(state, (&(*input).KeyPurposeId_key))))
	&& (encode_KeyPurposeId(state, (&(*input).KeyPurposeId))))
	&& (((encode_ExtKeyUsageSyntax(state, (&(*input).ExtKeyUsageSyntax_key))))
	&& (encode_ExtKeyUsageSyntax(state, (&(*input).ExtKeyUsageSyntax))))
	&& (((zcbor_uint32_encode(state, (&(*input).InhibitAnyPolicy_key))))
	&& (zcbor_uint32_encode(state, (&(*input).InhibitAnyPolicy))))
	&& (((encode_GeneralName(state, (&(*input).GeneralName_key))))
	&& (encode_GeneralName(state, (&(*input).GeneralName))))
	&& (((encode_GeneralNames(state, (&(*input).GeneralNames_key))))
	&& (encode_GeneralNames(state, (&(*input).GeneralNames))))
	&& (((encode_SubjectAltName(state, (&(*input).SubjectAltName_key))))
	&& (encode_SubjectAltName(state, (&(*input).SubjectAltName))))
	&& (((encode_IssuerAltName(state, (&(*input).IssuerAltName_key))))
	&& (encode_IssuerAltName(state, (&(*input).IssuerAltName))))
	&& (((encode_DistributionPointName(state, (&(*input).DistributionPointName_key))))
	&& (encode_DistributionPointName(state, (&(*input).DistributionPointName))))
	&& (((encode_CRLDistributionPoints(state, (&(*input).CRLDistributionPoints_key))))
	&& (encode_CRLDistributionPoints(state, (&(*input).CRLDistributionPoints))))
	&& (((encode_AccessDescription(state, (&(*input).AccessDescription_key))))
	&& (encode_AccessDescription(state, (&(*input).AccessDescription))))
	&& (((encode_AuthorityInfoAccessSyntax(state, (&(*input).AuthorityInfoAccessSyntax_key))))
	&& (encode_AuthorityInfoAccessSyntax(state, (&(*input).AuthorityInfoAccessSyntax))))
	&& (((encode_KeyIdentifierArray(state, (&(*input).KeyIdentifierArray_key))))
	&& (encode_KeyIdentifierArray(state, (&(*input).KeyIdentifierArray))))
	&& (((encode_AuthorityKeyIdentifier(state, (&(*input).AuthorityKeyIdentifier_key))))
	&& (encode_AuthorityKeyIdentifier(state, (&(*input).AuthorityKeyIdentifier))))
	&& (((encode_PolicyIdentifier(state, (&(*input).PolicyIdentifier_key))))
	&& (encode_PolicyIdentifier(state, (&(*input).PolicyIdentifier))))
	&& (((encode_PolicyQualifierInfo(state, (&(*input).PolicyQualifierInfo_key))))
	&& (encode_PolicyQualifierInfo(state, (&(*input).PolicyQualifierInfo))))
	&& (((encode_CertificatePolicies(state, (&(*input).CertificatePolicies_key))))
	&& (encode_CertificatePolicies(state, (&(*input).CertificatePolicies))))
	&& (((encode_GeneralSubtrees(state, (&(*input).GeneralSubtrees_key))))
	&& (encode_GeneralSubtrees(state, (&(*input).GeneralSubtrees))))
	&& (((encode_NameConstraints(state, (&(*input).NameConstraints_key))))
	&& (encode_NameConstraints(state, (&(*input).NameConstraints))))
	&& (((encode_Attributes(state, (&(*input).Attributes_key))))
	&& (encode_Attributes(state, (&(*input).Attributes))))
	&& (((encode_SubjectDirectoryAttributes(state, (&(*input).SubjectDirectoryAttributes_key))))
	&& (encode_SubjectDirectoryAttributes(state, (&(*input).SubjectDirectoryAttributes))))
	&& (((encode_ASIdOrRange(state, (&(*input).ASIdOrRange_key))))
	&& (encode_ASIdOrRange(state, (&(*input).ASIdOrRange))))
	&& (((encode_ASIdentifiers(state, (&(*input).ASIdentifiers_key))))
	&& (encode_ASIdentifiers(state, (&(*input).ASIdentifiers))))
	&& (((zcbor_bstr_encode(state, (&(*input).Address_key))))
	&& (zcbor_bstr_encode(state, (&(*input).Address))))
	&& (((encode_AddressPrefix(state, (&(*input).AddressPrefix_key))))
	&& (encode_AddressPrefix(state, (&(*input).AddressPrefix))))
	&& (((encode_AddressRange(state, (&(*input).AddressRange_key))))
	&& (encode_AddressRange(state, (&(*input).AddressRange))))
	&& (((encode_IPAddressOrRange(state, (&(*input).IPAddressOrRange_key))))
	&& (encode_IPAddressOrRange(state, (&(*input).IPAddressOrRange))))
	&& (((encode_IPAddressChoice(state, (&(*input).IPAddressChoice_key))))
	&& (encode_IPAddressChoice(state, (&(*input).IPAddressChoice))))
	&& (((encode_IPAddressFamily(state, (&(*input).IPAddressFamily_key))))
	&& (encode_IPAddressFamily(state, (&(*input).IPAddressFamily))))
	&& (((encode_IPAddrBlocks(state, (&(*input).IPAddrBlocks_key))))
	&& (encode_IPAddrBlocks(state, (&(*input).IPAddrBlocks))))
	&& (((encode_SignedCertificateTimestamp(state, (&(*input).SignedCertificateTimestamp_key))))
	&& (encode_SignedCertificateTimestamp(state, (&(*input).SignedCertificateTimestamp))))
	&& (((encode_SignedCertificateTimestamps(state, (&(*input).SignedCertificateTimestamps_key))))
	&& (encode_SignedCertificateTimestamps(state, (&(*input).SignedCertificateTimestamps))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_map_end_encode(state, 67))));

	log_result(state, res, __func__);
	return res;
}



int cbor_encode_All(
		uint8_t *payload, size_t payload_len,
		const struct All *input,
		size_t *payload_len_out)
{
	zcbor_state_t states[13];

	return zcbor_entry_function(payload, payload_len, (void *)input, payload_len_out, states,
		(zcbor_decoder_t *)encode_All, sizeof(states) / sizeof(zcbor_state_t), 1);
}
