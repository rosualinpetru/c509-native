// IGNORE THIS
// KEPT ONLY FOR INSPIRATION




// #include <stdint.h>
// #include <stdbool.h>
// #include <stddef.h>
// #include <string.h>
// #include <zcbor_decode.h>
// #include <zcbor_print.h>

// #include <c509_decode.hpp>

// #define log_result(state, result, func) do { \
// 	if (!result) { \
// 		zcbor_trace_file(state); \
// 		zcbor_log("%s error: %s\r\n", func, zcbor_error_str(zcbor_peek_error(state))); \
// 	} else { \
// 		zcbor_log("%s success\r\n", func); \
// 	} \
// } while(0)

// static bool decode_biguint(zcbor_state_t *state, struct zcbor_string *result);
// static bool decode_oid(zcbor_state_t *state, struct zcbor_string *result);
// static bool decode_AlgorithmIdentifier(zcbor_state_t *state, struct AlgorithmIdentifier_r *result);
// static bool decode_Attribute(zcbor_state_t *state, struct Attribute_r *result);
// static bool decode_Name(zcbor_state_t *state, struct Name_r *result);
// static bool decode_number(zcbor_state_t *state, struct number_r *result);
// static bool decode_time(zcbor_state_t *state, struct number_r *result);
// static bool decode_Extension(zcbor_state_t *state, struct Extension_r *result);
// static bool decode_Extensions(zcbor_state_t *state, struct Extensions_r *result);
// static bool decode_TBSCertificate(zcbor_state_t *state, struct TBSCertificate *result);
// static bool decode_C509Certificate(zcbor_state_t *state, struct C509Certificate *result);
// static bool decode_repeated_PolicyMappings_issuerDomainPolicy_l(zcbor_state_t *state, struct PolicyMappings_issuerDomainPolicy_l *result);
// static bool decode_PolicyMappings(zcbor_state_t *state, struct PolicyMappings *result);
// static bool decode_PolicyConstraints(zcbor_state_t *state, struct PolicyConstraints *result);
// static bool decode_KeyPurposeId(zcbor_state_t *state, struct KeyPurposeId_r *result);
// static bool decode_ExtKeyUsageSyntax(zcbor_state_t *state, struct ExtKeyUsageSyntax_r *result);
// static bool decode_GeneralName(zcbor_state_t *state, struct GeneralName *result);
// static bool decode_GeneralNames(zcbor_state_t *state, struct GeneralNames *result);
// static bool decode_SubjectAltName(zcbor_state_t *state, struct SubjectAltName_r *result);
// static bool decode_IssuerAltName(zcbor_state_t *state, struct IssuerAltName_r *result);
// static bool decode_DistributionPointName(zcbor_state_t *state, struct DistributionPointName_r *result);
// static bool decode_CRLDistributionPoints(zcbor_state_t *state, struct CRLDistributionPoints *result);
// static bool decode_uri(zcbor_state_t *state, struct zcbor_string *result);
// static bool decode_AccessDescription(zcbor_state_t *state, struct AccessDescription *result);
// static bool decode_AuthorityInfoAccessSyntax(zcbor_state_t *state, struct AuthorityInfoAccessSyntax *result);
// static bool decode_KeyIdentifierArray(zcbor_state_t *state, struct KeyIdentifierArray *result);
// static bool decode_AuthorityKeyIdentifier(zcbor_state_t *state, struct AuthorityKeyIdentifier_r *result);
// static bool decode_PolicyIdentifier(zcbor_state_t *state, struct PolicyIdentifier_r *result);
// static bool decode_PolicyQualifierInfo(zcbor_state_t *state, struct PolicyQualifierInfo *result);
// static bool decode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l(zcbor_state_t *state, struct PolicyIdentifier_m_l_PolicyQualifierInfo_m_l *result);
// static bool decode_repeated_CertificatePolicies_PolicyIdentifier_m_l(zcbor_state_t *state, struct CertificatePolicies_PolicyIdentifier_m_l *result);
// static bool decode_CertificatePolicies(zcbor_state_t *state, struct CertificatePolicies *result);
// static bool decode_GeneralSubtrees(zcbor_state_t *state, struct GeneralSubtrees *result);
// static bool decode_NameConstraints(zcbor_state_t *state, struct NameConstraints *result);
// static bool decode_Attributes(zcbor_state_t *state, struct Attributes_r *result);
// static bool decode_SubjectDirectoryAttributes(zcbor_state_t *state, struct SubjectDirectoryAttributes *result);
// static bool decode_ASIdOrRange(zcbor_state_t *state, struct ASIdOrRange_r *result);
// static bool decode_ASIdentifiers(zcbor_state_t *state, struct ASIdentifiers_r *result);
// static bool decode_AddressPrefix(zcbor_state_t *state, struct AddressPrefix *result);
// static bool decode_AddressRange(zcbor_state_t *state, struct AddressRange *result);
// static bool decode_IPAddressOrRange(zcbor_state_t *state, struct IPAddressOrRange_r *result);
// static bool decode_IPAddressChoice(zcbor_state_t *state, struct IPAddressChoice_r *result);
// static bool decode_IPAddressFamily(zcbor_state_t *state, struct IPAddressFamily *result);
// static bool decode_IPAddrBlocks(zcbor_state_t *state, struct IPAddrBlocks *result);
// static bool decode_SignedCertificateTimestamp(zcbor_state_t *state, struct SignedCertificateTimestamp *result);
// static bool decode_SignedCertificateTimestamps(zcbor_state_t *state, struct SignedCertificateTimestamps *result);
// static bool decode_All(zcbor_state_t *state, struct All *result);


// static bool decode_biguint(
// 		zcbor_state_t *state, struct zcbor_string *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_expect(state, 2)
// 	&& (zcbor_bstr_decode(state, (&(*result))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_oid(
// 		zcbor_state_t *state, struct zcbor_string *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_expect(state, 111)
// 	&& (zcbor_bstr_decode(state, (&(*result))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_AlgorithmIdentifier(
// 		zcbor_state_t *state, struct AlgorithmIdentifier_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).AlgorithmIdentifier_choice = AlgorithmIdentifier_int_c), true))
// 	|| (((decode_oid(state, (&(*result).oid_m)))) && (((*result).AlgorithmIdentifier_choice = AlgorithmIdentifier_oid_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_list_start_decode(state) && ((((decode_oid(state, (&(*result).algorithm))))
// 	&& ((zcbor_bstr_decode(state, (&(*result).parameters))))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).AlgorithmIdentifier_choice = AlgorithmIdentifier_algorithm_l_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_Attribute(
// 		zcbor_state_t *state, struct Attribute_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((((zcbor_int32_decode(state, (&(*result).attributeTypeInt))))
// 	&& ((zcbor_tstr_decode(state, (&(*result).attributeValueText)))))) && (((*result).Attribute_choice = Attribute_attributeTypeInt_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((((decode_oid(state, (&(*result).attributeTypeOID))))
// 	&& ((zcbor_bstr_decode(state, (&(*result).attributeValueBytes)))))) && (((*result).Attribute_choice = Attribute_attributeTypeOID_l_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_Name(
// 		zcbor_state_t *state, struct Name_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_list_start_decode(state) && ((zcbor_multi_decode(0, 1024, &(*result).Attribute_m_count, (zcbor_decoder_t *)decode_Attribute, state, (*&(*result).Attribute_m), sizeof(struct Attribute_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).Name_choice = Name_Attribute_m_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_tstr_decode(state, (&(*result).text_m)))) && (((*result).Name_choice = Name_text_m_c), true)))
// 	|| (((zcbor_bstr_decode(state, (&(*result).bytes_m)))) && (((*result).Name_choice = Name_bytes_m_c), true))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_Attribute(state, (*&(*result).Attribute_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_number(
// 		zcbor_state_t *state, struct number_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).number_choice = number_int_c), true))
// 	|| (((zcbor_float_decode(state, (&(*result).Float)))) && (((*result).number_choice = number_float_c), true))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_time(
// 		zcbor_state_t *state, struct number_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_expect(state, 1)
// 	&& (decode_number(state, (&(*result))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_Extension(
// 		zcbor_state_t *state, struct Extension_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((((zcbor_int32_decode(state, (&(*result).extensionIDInt))))
// 	&& ((zcbor_any_skip(state, NULL))))) && (((*result).Extension_choice = Extension_extensionIDInt_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((((decode_oid(state, (&(*result).extensionIDOID))))
// 	&& ((*result).critical_present = ((zcbor_bool_expect(state, (true)))), 1)
// 	&& ((zcbor_bstr_decode(state, (&(*result).extensionValueBytes)))))) && (((*result).Extension_choice = Extension_extensionIDOID_l_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_Extensions(
// 		zcbor_state_t *state, struct Extensions_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_list_start_decode(state) && ((zcbor_multi_decode(0, 1024, &(*result).Extension_m_count, (zcbor_decoder_t *)decode_Extension, state, (*&(*result).Extension_m), sizeof(struct Extension_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).Extensions_choice = Extensions_Extension_m_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).Extensions_choice = Extensions_int_c), true)))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_Extension(state, (*&(*result).Extension_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_TBSCertificate(
// 		zcbor_state_t *state, struct TBSCertificate *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((((zcbor_int32_decode(state, (&(*result).c509CertificateType))))
// 	&& ((decode_biguint(state, (&(*result).certificateSerialNumber))))
// 	&& ((decode_AlgorithmIdentifier(state, (&(*result).issuerSignatureAlgorithm))))
// 	&& ((zcbor_union_start_code(state) && (int_res = ((((decode_Name(state, (&(*result).Name_m)))) && (((*result).issuer_choice = TBSCertificate_issuer_Name_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_nil_expect(state, NULL))) && (((*result).issuer_choice = TBSCertificate_issuer_null_m_c), true)))), zcbor_union_end_code(state), int_res)))
// 	&& ((decode_time(state, (&(*result).validityNotBefore))))
// 	&& ((zcbor_union_start_code(state) && (int_res = ((((decode_time(state, (&(*result).time_m)))) && (((*result).validityNotAfter_choice = TBSCertificate_validityNotAfter_time_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_nil_expect(state, NULL))) && (((*result).validityNotAfter_choice = TBSCertificate_validityNotAfter_null_m_c), true)))), zcbor_union_end_code(state), int_res)))
// 	&& ((decode_Name(state, (&(*result).subject))))
// 	&& ((decode_AlgorithmIdentifier(state, (&(*result).subjectPublicKeyAlgorithm))))
// 	&& ((zcbor_any_skip(state, NULL)))
// 	&& ((decode_Extensions(state, (&(*result).extensions)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }


// static bool decode_repeated_PolicyMappings_issuerDomainPolicy_l(
// 		zcbor_state_t *state, struct PolicyMappings_issuerDomainPolicy_l *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((decode_oid(state, (&(*result).issuerDomainPolicy))))
// 	&& ((decode_oid(state, (&(*result).subjectDomainPolicy)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_PolicyMappings(
// 		zcbor_state_t *state, struct PolicyMappings *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).issuerDomainPolicy_l_count, (zcbor_decoder_t *)decode_repeated_PolicyMappings_issuerDomainPolicy_l, state, (*&(*result).issuerDomainPolicy_l), sizeof(struct PolicyMappings_issuerDomainPolicy_l))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_repeated_PolicyMappings_issuerDomainPolicy_l(state, (*&(*result).issuerDomainPolicy_l));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_PolicyConstraints(
// 		zcbor_state_t *state, struct PolicyConstraints *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_list_start_decode(state) && ((((zcbor_union_start_code(state) && (int_res = ((((zcbor_uint32_decode(state, (&(*result).uint)))) && (((*result).requireExplicitPolicy_choice = PolicyConstraints_requireExplicitPolicy_uint_c), true))
// 	|| (((zcbor_nil_expect(state, NULL))) && (((*result).requireExplicitPolicy_choice = PolicyConstraints_requireExplicitPolicy_null_m_c), true))), zcbor_union_end_code(state), int_res)))
// 	&& ((zcbor_union_start_code(state) && (int_res = ((((zcbor_uint32_decode(state, (&(*result).uint)))) && (((*result).inhibitPolicyMapping_choice = PolicyConstraints_inhibitPolicyMapping_uint_c), true))
// 	|| (((zcbor_nil_expect(state, NULL))) && (((*result).inhibitPolicyMapping_choice = PolicyConstraints_inhibitPolicyMapping_null_m_c), true))), zcbor_union_end_code(state), int_res)))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_KeyPurposeId(
// 		zcbor_state_t *state, struct KeyPurposeId_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).KeyPurposeId_choice = KeyPurposeId_int_c), true))
// 	|| (((decode_oid(state, (&(*result).oid_m)))) && (((*result).KeyPurposeId_choice = KeyPurposeId_oid_m_c), true))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_ExtKeyUsageSyntax(
// 		zcbor_state_t *state, struct ExtKeyUsageSyntax_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_list_start_decode(state) && ((zcbor_multi_decode(2, 1024, &(*result).KeyPurposeId_m_count, (zcbor_decoder_t *)decode_KeyPurposeId, state, (*&(*result).KeyPurposeId_m), sizeof(struct KeyPurposeId_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).ExtKeyUsageSyntax_choice = ExtKeyUsageSyntax_KeyPurposeId_m_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((decode_KeyPurposeId(state, (&(*result).KeyPurposeId_m)))) && (((*result).ExtKeyUsageSyntax_choice = ExtKeyUsageSyntax_KeyPurposeId_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_KeyPurposeId(state, (*&(*result).KeyPurposeId_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_GeneralName(
// 		zcbor_state_t *state, struct GeneralName *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((zcbor_int32_decode(state, (&(*result).GeneralNameType))))
// 	&& ((zcbor_any_skip(state, NULL))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_GeneralNames(
// 		zcbor_state_t *state, struct GeneralNames *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).GeneralName_m_count, (zcbor_decoder_t *)decode_GeneralName, state, (*&(*result).GeneralName_m), sizeof(struct GeneralName))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_GeneralName(state, (*&(*result).GeneralName_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_SubjectAltName(
// 		zcbor_state_t *state, struct SubjectAltName_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((decode_GeneralNames(state, (&(*result).GeneralNames_m)))) && (((*result).SubjectAltName_choice = SubjectAltName_GeneralNames_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_tstr_decode(state, (&(*result).text_m)))) && (((*result).SubjectAltName_choice = SubjectAltName_text_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_IssuerAltName(
// 		zcbor_state_t *state, struct IssuerAltName_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((decode_GeneralNames(state, (&(*result).GeneralNames_m)))) && (((*result).IssuerAltName_choice = IssuerAltName_GeneralNames_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_tstr_decode(state, (&(*result).text_m)))) && (((*result).IssuerAltName_choice = IssuerAltName_text_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_DistributionPointName(
// 		zcbor_state_t *state, struct DistributionPointName_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_list_start_decode(state) && ((zcbor_multi_decode(2, 1024, &(*result).text_m_count, (zcbor_decoder_t *)zcbor_tstr_decode, state, (*&(*result).text_m), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).DistributionPointName_choice = DistributionPointName_text_m_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_tstr_decode(state, (&(*result).text_m)))) && (((*result).DistributionPointName_choice = DistributionPointName_text_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		zcbor_tstr_decode(state, (*&(*result).text_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_CRLDistributionPoints(
// 		zcbor_state_t *state, struct CRLDistributionPoints *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).DistributionPointName_m_count, (zcbor_decoder_t *)decode_DistributionPointName, state, (*&(*result).DistributionPointName_m), sizeof(struct DistributionPointName_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_DistributionPointName(state, (*&(*result).DistributionPointName_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_uri(
// 		zcbor_state_t *state, struct zcbor_string *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_expect(state, 32)
// 	&& (zcbor_tstr_decode(state, (&(*result))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_AccessDescription(
// 		zcbor_state_t *state, struct AccessDescription *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((((zcbor_union_start_code(state) && (int_res = ((((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).accessMethod_choice = AccessDescription_accessMethod_int_c), true))
// 	|| (((decode_oid(state, (&(*result).oid_m)))) && (((*result).accessMethod_choice = AccessDescription_accessMethod_oid_m_c), true))), zcbor_union_end_code(state), int_res)))
// 	&& (((decode_uri(state, (&(*result).uri_key))))
// 	&& (zcbor_tstr_decode(state, (&(*result).uri)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_AuthorityInfoAccessSyntax(
// 		zcbor_state_t *state, struct AuthorityInfoAccessSyntax *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).AccessDescription_m_count, (zcbor_decoder_t *)decode_AccessDescription, state, (*&(*result).AccessDescription_m), sizeof(struct AccessDescription))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_AccessDescription(state, (*&(*result).AccessDescription_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_KeyIdentifierArray(
// 		zcbor_state_t *state, struct KeyIdentifierArray *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((((zcbor_bstr_decode(state, (&(*result).keyIdentifier))))
// 	&& ((decode_GeneralNames(state, (&(*result).authorityCertIssuer))))
// 	&& ((decode_biguint(state, (&(*result).authorityCertSerialNumber))))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_AuthorityKeyIdentifier(
// 		zcbor_state_t *state, struct AuthorityKeyIdentifier_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((decode_KeyIdentifierArray(state, (&(*result).KeyIdentifierArray_m)))) && (((*result).AuthorityKeyIdentifier_choice = AuthorityKeyIdentifier_KeyIdentifierArray_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_bstr_decode(state, (&(*result).KeyIdentifier_m)))) && (((*result).AuthorityKeyIdentifier_choice = AuthorityKeyIdentifier_KeyIdentifier_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_PolicyIdentifier(
// 		zcbor_state_t *state, struct PolicyIdentifier_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).PolicyIdentifier_choice = PolicyIdentifier_int_c), true))
// 	|| (((decode_oid(state, (&(*result).oid_m)))) && (((*result).PolicyIdentifier_choice = PolicyIdentifier_oid_m_c), true))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_PolicyQualifierInfo(
// 		zcbor_state_t *state, struct PolicyQualifierInfo *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((((zcbor_union_start_code(state) && (int_res = ((((zcbor_int32_decode(state, (&(*result).Int)))) && (((*result).policyQualifierId_choice = PolicyQualifierInfo_policyQualifierId_int_c), true))
// 	|| (((decode_oid(state, (&(*result).oid_m)))) && (((*result).policyQualifierId_choice = PolicyQualifierInfo_policyQualifierId_oid_m_c), true))), zcbor_union_end_code(state), int_res)))
// 	&& ((zcbor_tstr_decode(state, (&(*result).qualifier)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l(
// 		zcbor_state_t *state, struct PolicyIdentifier_m_l_PolicyQualifierInfo_m_l *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).PolicyQualifierInfo_m_count, (zcbor_decoder_t *)decode_PolicyQualifierInfo, state, (*&(*result).PolicyQualifierInfo_m), sizeof(struct PolicyQualifierInfo))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_PolicyQualifierInfo(state, (*&(*result).PolicyQualifierInfo_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_repeated_CertificatePolicies_PolicyIdentifier_m_l(
// 		zcbor_state_t *state, struct CertificatePolicies_PolicyIdentifier_m_l *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((decode_PolicyIdentifier(state, (&(*result).PolicyIdentifier_m))))
// 	&& (zcbor_present_decode(&((*result).PolicyQualifierInfo_m_l_present), (zcbor_decoder_t *)decode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l, state, (&(*result).PolicyQualifierInfo_m_l))))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_repeated_PolicyIdentifier_m_l_PolicyQualifierInfo_m_l(state, (&(*result).PolicyQualifierInfo_m_l));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_CertificatePolicies(
// 		zcbor_state_t *state, struct CertificatePolicies *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).PolicyIdentifier_m_l_count, (zcbor_decoder_t *)decode_repeated_CertificatePolicies_PolicyIdentifier_m_l, state, (*&(*result).PolicyIdentifier_m_l), sizeof(struct CertificatePolicies_PolicyIdentifier_m_l))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_repeated_CertificatePolicies_PolicyIdentifier_m_l(state, (*&(*result).PolicyIdentifier_m_l));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_GeneralSubtrees(
// 		zcbor_state_t *state, struct GeneralSubtrees *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).GeneralName_m_count, (zcbor_decoder_t *)decode_GeneralName, state, (*&(*result).GeneralName_m), sizeof(struct GeneralName))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_GeneralName(state, (*&(*result).GeneralName_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_NameConstraints(
// 		zcbor_state_t *state, struct NameConstraints *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_list_start_decode(state) && ((((zcbor_union_start_code(state) && (int_res = ((((decode_GeneralSubtrees(state, (&(*result).GeneralSubtrees_m)))) && (((*result).permittedSubtrees_choice = NameConstraints_permittedSubtrees_GeneralSubtrees_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_nil_expect(state, NULL))) && (((*result).permittedSubtrees_choice = NameConstraints_permittedSubtrees_null_m_c), true)))), zcbor_union_end_code(state), int_res)))
// 	&& ((zcbor_union_start_code(state) && (int_res = ((((decode_GeneralSubtrees(state, (&(*result).GeneralSubtrees_m)))) && (((*result).excludedSubtrees_choice = NameConstraints_excludedSubtrees_GeneralSubtrees_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_nil_expect(state, NULL))) && (((*result).excludedSubtrees_choice = NameConstraints_excludedSubtrees_null_m_c), true)))), zcbor_union_end_code(state), int_res)))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_Attributes(
// 		zcbor_state_t *state, struct Attributes_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((((zcbor_int32_decode(state, (&(*result).attributeTypesInt))))
// 	&& ((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).text_m_count, (zcbor_decoder_t *)zcbor_tstr_decode, state, (*&(*result).text_m), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))))) && (((*result).Attributes_choice = Attributes_attributeTypesInt_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((((decode_oid(state, (&(*result).attributeTypesOID))))
// 	&& ((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).bytes_m_count, (zcbor_decoder_t *)zcbor_bstr_decode, state, (*&(*result).bytes_m), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))))) && (((*result).Attributes_choice = Attributes_attributeTypesOID_l_c), true)))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		zcbor_tstr_decode(state, (*&(*result).text_m));
// 		zcbor_bstr_decode(state, (*&(*result).bytes_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_SubjectDirectoryAttributes(
// 		zcbor_state_t *state, struct SubjectDirectoryAttributes *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).Attributes_m_count, (zcbor_decoder_t *)decode_Attributes, state, (*&(*result).Attributes_m), sizeof(struct Attributes_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_Attributes(state, (*&(*result).Attributes_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_ASIdOrRange(
// 		zcbor_state_t *state, struct ASIdOrRange_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_uint32_decode(state, (&(*result).uint)))) && (((*result).ASIdOrRange_choice = ASIdOrRange_uint_c), true))
// 	|| (((zcbor_list_start_decode(state) && ((((zcbor_uint32_decode(state, (&(*result).min))))
// 	&& ((zcbor_uint32_decode(state, (&(*result).max))))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).ASIdOrRange_choice = ASIdOrRange_min_l_c), true))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_ASIdentifiers(
// 		zcbor_state_t *state, struct ASIdentifiers_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).ASIdOrRange_m_count, (zcbor_decoder_t *)decode_ASIdOrRange, state, (*&(*result).ASIdOrRange_m), sizeof(struct ASIdOrRange_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).ASIdentifiers_choice = ASIdentifiers_ASIdOrRange_m_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_nil_expect(state, NULL))) && (((*result).ASIdentifiers_choice = ASIdentifiers_null_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_ASIdOrRange(state, (*&(*result).ASIdOrRange_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_AddressPrefix(
// 		zcbor_state_t *state, struct AddressPrefix *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((zcbor_bstr_decode(state, (&(*result).Address_m))))
// 	&& ((zcbor_uint32_decode(state, (&(*result).unusedBits)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_AddressRange(
// 		zcbor_state_t *state, struct AddressRange *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((((zcbor_bstr_decode(state, (&(*result).min))))
// 	&& ((zcbor_bstr_decode(state, (&(*result).max))))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_IPAddressOrRange(
// 		zcbor_state_t *state, struct IPAddressOrRange_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((decode_AddressPrefix(state, (&(*result).AddressPrefix_m)))) && (((*result).IPAddressOrRange_choice = IPAddressOrRange_AddressPrefix_m_c), true))
// 	|| (zcbor_union_elem_code(state) && (((decode_AddressRange(state, (&(*result).AddressRange_m)))) && (((*result).IPAddressOrRange_choice = IPAddressOrRange_AddressRange_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_IPAddressChoice(
// 		zcbor_state_t *state, struct IPAddressChoice_r *result)
// {
// 	zcbor_log("%s\r\n", __func__);
// 	bool int_res;

// 	bool res = (((zcbor_union_start_code(state) && (int_res = ((((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).IPAddressOrRange_m_count, (zcbor_decoder_t *)decode_IPAddressOrRange, state, (*&(*result).IPAddressOrRange_m), sizeof(struct IPAddressOrRange_r))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))) && (((*result).IPAddressChoice_choice = IPAddressChoice_IPAddressOrRange_m_l_c), true))
// 	|| (zcbor_union_elem_code(state) && (((zcbor_nil_expect(state, NULL))) && (((*result).IPAddressChoice_choice = IPAddressChoice_null_m_c), true)))), zcbor_union_end_code(state), int_res))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_IPAddressOrRange(state, (*&(*result).IPAddressOrRange_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_IPAddressFamily(
// 		zcbor_state_t *state, struct IPAddressFamily *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((zcbor_uint32_decode(state, (&(*result).AFI))))
// 	&& ((decode_IPAddressChoice(state, (&(*result).IPAddressChoice_m)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_IPAddrBlocks(
// 		zcbor_state_t *state, struct IPAddrBlocks *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).IPAddressFamily_m_count, (zcbor_decoder_t *)decode_IPAddressFamily, state, (*&(*result).IPAddressFamily_m), sizeof(struct IPAddressFamily))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_IPAddressFamily(state, (*&(*result).IPAddressFamily_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_SignedCertificateTimestamp(
// 		zcbor_state_t *state, struct SignedCertificateTimestamp *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((zcbor_bstr_decode(state, (&(*result).logID))))
// 	&& ((zcbor_int32_decode(state, (&(*result).timestamp))))
// 	&& ((decode_AlgorithmIdentifier(state, (&(*result).sigAlg))))
// 	&& ((zcbor_any_skip(state, NULL))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool decode_SignedCertificateTimestamps(
// 		zcbor_state_t *state, struct SignedCertificateTimestamps *result)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((zcbor_list_start_decode(state) && ((zcbor_multi_decode(1, 1024, &(*result).SignedCertificateTimestamp_m_count, (zcbor_decoder_t *)decode_SignedCertificateTimestamp, state, (*&(*result).SignedCertificateTimestamp_m), sizeof(struct SignedCertificateTimestamp))) || (zcbor_list_map_end_force_decode(state), false)) && zcbor_list_end_decode(state))));

// 	if (false) {
// 		/* For testing that the types of the arguments are correct.
// 		 * A compiler error here means a bug in zcbor.
// 		 */
// 		decode_SignedCertificateTimestamp(state, (*&(*result).SignedCertificateTimestamp_m));
// 	}

// 	log_result(state, res, __func__);
// 	return res;
// }