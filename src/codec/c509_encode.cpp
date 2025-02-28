// IGNORE THIS
// KEPT ONLY FOR INSPIRATION

// #include <zcbor_encode.h>
// #include <zcbor_print.h>

// #include <c509_cbor_codec.hpp>

// #include "zcbor_log.cpp"

// using namespace CBOR::Prelude;

// static bool append_raw_cbor(zcbor_state_t *state, const Any any)
// {
// 	if ((state->payload + any.value.size()) > state->payload_end)
// 	{
// 		ZCBOR_ERR(ZCBOR_ERR_NO_PAYLOAD);
// 	}

// #ifdef ZCBOR_BIG_ENDIAN
// 	memcpy(state->payload_mut, u8_result, result_len);
// 	state->payload_mut += result_len;
// #else
// 	for (int i = ; result_len > 0; result_len--) {
// 		*(state->payload_mut++) = u8_result[result_len - 1];
// 	}
// #endif /* ZCBOR_BIG_ENDIAN */

// 	state->elem_count++;
// 	return true;

// 	// Advance the payload pointer
// 	state->payload += raw_data_len;
// }

// static bool encode_biguint(
// 	zcbor_state_t *state, const struct zcbor_string *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_put(state, 2) && (zcbor_bstr_encode(state, (&(*input))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_oid(
// 	zcbor_state_t *state, const struct zcbor_string *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_put(state, 111) && (zcbor_bstr_encode(state, (&(*input))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_AlgorithmIdentifier(
// 	zcbor_state_t *state, const struct AlgorithmIdentifier_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((*input).AlgorithmIdentifier_choice == AlgorithmIdentifier_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
// 																					 : (((*input).AlgorithmIdentifier_choice == AlgorithmIdentifier_oid_m_c) ? ((encode_oid(state, (&(*input).oid_m))))
// 																																							 : (((*input).AlgorithmIdentifier_choice == AlgorithmIdentifier_algorithm_l_c) ? ((zcbor_list_start_encode(state, 2) && ((((encode_oid(state, (&(*input).algorithm)))) && ((zcbor_bstr_encode(state, (&(*input).parameters))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2)))
// 																																																										   : false)))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_Attribute(
// 	zcbor_state_t *state, const struct Attribute_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((*input).Attribute_choice == Attribute_attributeTypeInt_l_c) ? ((((zcbor_int32_encode(state, (&(*input).attributeTypeInt)))) && ((zcbor_tstr_encode(state, (&(*input).attributeValueText))))))
// 																				: (((*input).Attribute_choice == Attribute_attributeTypeOID_l_c) ? ((((encode_oid(state, (&(*input).attributeTypeOID)))) && ((zcbor_bstr_encode(state, (&(*input).attributeValueBytes))))))
// 																																				 : false))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_Name(
// 	zcbor_state_t *state, const struct Name_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((*input).Name_choice == Name_Attribute_m_l_c) ? ((zcbor_list_start_encode(state, 2048) && ((zcbor_multi_encode_minmax(0, 1024, &(*input).Attribute_m_count, (zcbor_encoder_t *)encode_Attribute, state, (*&(*input).Attribute_m), sizeof(struct Attribute_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2048)))
// 																 : (((*input).Name_choice == Name_text_m_c) ? ((zcbor_tstr_encode(state, (&(*input).text_m))))
// 																											: (((*input).Name_choice == Name_bytes_m_c) ? ((zcbor_bstr_encode(state, (&(*input).bytes_m))))
// 																																						: false)))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_number(
// 	zcbor_state_t *state, const struct number_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((*input).number_choice == number_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
// 														   : (((*input).number_choice == number_float_c) ? ((zcbor_float64_encode(state, (&(*input).Float))))
// 																										 : false))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_time(
// 	zcbor_state_t *state, const struct number_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = ((zcbor_tag_put(state, 1) && (encode_number(state, (&(*input))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_Extension(
// 	zcbor_state_t *state, const struct Extension_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((*input).Extension_choice == Extension_extensionIDInt_l_c) ? ((((zcbor_int32_encode(state, (&(*input).extensionIDInt)))) && ((zcbor_nil_put(state, NULL)))))
// 																			  : (((*input).Extension_choice == Extension_extensionIDOID_l_c) ? ((((encode_oid(state, (&(*input).extensionIDOID)))) && (!(*input).critical_present || zcbor_bool_put(state, (true))) && ((zcbor_bstr_encode(state, (&(*input).extensionValueBytes))))))
// 																																			 : false))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_Extensions(
// 	zcbor_state_t *state, const struct Extensions_r *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((*input).Extensions_choice == Extensions_Extension_m_l_c) ? ((zcbor_list_start_encode(state, 3072) && ((zcbor_multi_encode_minmax(0, 1024, &(*input).Extension_m_count, (zcbor_encoder_t *)encode_Extension, state, (*&(*input).Extension_m), sizeof(struct Extension_r))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 3072)))
// 																			 : (((*input).Extensions_choice == Extensions_int_c) ? ((zcbor_int32_encode(state, (&(*input).Int))))
// 																																 : false))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_TBSCertificate(zcbor_state_t *state, const struct CBOR::C509::TBSCertificate *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((((zcbor_int32_encode(state, (&(*input).c509CertificateType)))) && ((encode_biguint(state, (&(*input).certificateSerialNumber)))) && ((encode_AlgorithmIdentifier(state, (&(*input).issuerSignatureAlgorithm)))) && ((((*input).issuer_choice == TBSCertificate_issuer_Name_m_c) ? ((encode_Name(state, (&(*input).Name_m)))) : (((*input).issuer_choice == TBSCertificate_issuer_null_m_c) ? ((zcbor_nil_put(state, NULL))) : false))) && ((encode_time(state, (&(*input).validityNotBefore)))) && ((((*input).validityNotAfter_choice == TBSCertificate_validityNotAfter_time_m_c) ? ((encode_time(state, (&(*input).time_m)))) : (((*input).validityNotAfter_choice == TBSCertificate_validityNotAfter_null_m_c) ? ((zcbor_nil_put(state, NULL))) : false))) && ((encode_Name(state, (&(*input).subject)))) && ((encode_AlgorithmIdentifier(state, (&(*input).subjectPublicKeyAlgorithm)))) && ((zcbor_nil_put(state, NULL))) && ((encode_Extensions(state, (&(*input).extensions)))))));

// 	log_result(state, res, __func__);
// 	return res;
// }

// static bool encode_Certificate(zcbor_state_t *state, const CBOR::C509::Certificate *input)
// {
// 	zcbor_log("%s\r\n", __func__);

// 	bool res = (((
// 		zcbor_list_start_encode(state, 2) &&
// 		((((encode_TBSCertificate(state, &input->tbsCertificate))) && ((zcbor_nil_put(state, NULL)))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 2))));

// 	zcbor_put

// 		log_result(state, res, __func__);
// 	return res;
// }

// int CBOR::C509::Codec::cbor_encode_c509(uint8_t *payload, size_t payload_len, const CBOR::C509::Certificate *input, size_t *payload_len_out)
// {
// 	zcbor_state_t states[13];

// 	return zcbor_entry_function(
// 		payload, payload_len,
// 		(void *)input, payload_len_out, states,
// 		(zcbor_decoder_t *)encode_Certificate, sizeof(states) / sizeof(zcbor_state_t),
// 		1);
// }
