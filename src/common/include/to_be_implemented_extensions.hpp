// struct PolicyMappings_issuerDomainPolicy_l
// {
// 	struct zcbor_string issuerDomainPolicy;
// 	struct zcbor_string subjectDomainPolicy;
// };

// struct PolicyMappings
// {
// 	struct PolicyMappings_issuerDomainPolicy_l issuerDomainPolicy_l[1024];
// 	size_t issuerDomainPolicy_l_count;
// };

// struct PolicyConstraints
// {
// 	union
// 	{
// 		uint32_t uint;
// 	};
// 	enum
// 	{
// 		PolicyConstraints_requireExplicitPolicy_uint_c,
// 		PolicyConstraints_requireExplicitPolicy_null_m_c,
// 	} requireExplicitPolicy_choice;
// 	union
// 	{
// 		uint32_t uint;
// 	};
// 	enum
// 	{
// 		PolicyConstraints_inhibitPolicyMapping_uint_c,
// 		PolicyConstraints_inhibitPolicyMapping_null_m_c,
// 	} inhibitPolicyMapping_choice;
// };

// struct KeyPurposeId_r
// {
// 	union
// 	{
// 		int32_t Int;
// 		struct zcbor_string oid_m;
// 	};
// 	enum
// 	{
// 		KeyPurposeId_int_c,
// 		KeyPurposeId_oid_m_c,
// 	} KeyPurposeId_choice;
// };

// struct ExtKeyUsageSyntax_r
// {
// 	union
// 	{
// 		struct
// 		{
// 			struct KeyPurposeId_r KeyPurposeId_m[1024];
// 			size_t KeyPurposeId_m_count;
// 		};
// 		struct KeyPurposeId_r KeyPurposeId_m;
// 	};
// 	enum
// 	{
// 		ExtKeyUsageSyntax_KeyPurposeId_m_l_c,
// 		ExtKeyUsageSyntax_KeyPurposeId_m_c,
// 	} ExtKeyUsageSyntax_choice;
// };

// struct GeneralName
// {
// 	int32_t GeneralNameType;
// };

// struct GeneralNames
// {
// 	struct GeneralName GeneralName_m[1024];
// 	size_t GeneralName_m_count;
// };

// struct SubjectAltName_r
// {
// 	union
// 	{
// 		struct GeneralNames GeneralNames_m;
// 		struct zcbor_string text_m;
// 	};
// 	enum
// 	{
// 		SubjectAltName_GeneralNames_m_c,
// 		SubjectAltName_text_m_c,
// 	} SubjectAltName_choice;
// };

// struct IssuerAltName_r
// {
// 	union
// 	{
// 		struct GeneralNames GeneralNames_m;
// 		struct zcbor_string text_m;
// 	};
// 	enum
// 	{
// 		IssuerAltName_GeneralNames_m_c,
// 		IssuerAltName_text_m_c,
// 	} IssuerAltName_choice;
// };

// struct DistributionPointName_r
// {
// 	union
// 	{
// 		struct
// 		{
// 			struct zcbor_string text_m[1024];
// 			size_t text_m_count;
// 		};
// 		struct zcbor_string text_m;
// 	};
// 	enum
// 	{
// 		DistributionPointName_text_m_l_c,
// 		DistributionPointName_text_m_c,
// 	} DistributionPointName_choice;
// };

// struct CRLDistributionPoints
// {
// 	struct DistributionPointName_r DistributionPointName_m[1024];
// 	size_t DistributionPointName_m_count;
// };

// struct AccessDescription
// {
// 	union
// 	{
// 		int32_t Int;
// 		struct zcbor_string oid_m;
// 	};
// 	enum
// 	{
// 		AccessDescription_accessMethod_int_c,
// 		AccessDescription_accessMethod_oid_m_c,
// 	} accessMethod_choice;
// 	struct zcbor_string uri_key;
// 	struct zcbor_string uri;
// };

// struct AuthorityInfoAccessSyntax
// {
// 	struct AccessDescription AccessDescription_m[1024];
// 	size_t AccessDescription_m_count;
// };

// struct KeyIdentifierArray
// {
// 	struct zcbor_string keyIdentifier;
// 	struct GeneralNames authorityCertIssuer;
// 	struct zcbor_string authorityCertSerialNumber;
// };

// struct AuthorityKeyIdentifier_r
// {
// 	union
// 	{
// 		struct KeyIdentifierArray KeyIdentifierArray_m;
// 		struct zcbor_string KeyIdentifier_m;
// 	};
// 	enum
// 	{
// 		AuthorityKeyIdentifier_KeyIdentifierArray_m_c,
// 		AuthorityKeyIdentifier_KeyIdentifier_m_c,
// 	} AuthorityKeyIdentifier_choice;
// };

// struct PolicyIdentifier_r
// {
// 	union
// 	{
// 		int32_t Int;
// 		struct zcbor_string oid_m;
// 	};
// 	enum
// 	{
// 		PolicyIdentifier_int_c,
// 		PolicyIdentifier_oid_m_c,
// 	} PolicyIdentifier_choice;
// };

// struct PolicyQualifierInfo
// {
// 	union
// 	{
// 		int32_t Int;
// 		struct zcbor_string oid_m;
// 	};
// 	enum
// 	{
// 		PolicyQualifierInfo_policyQualifierId_int_c,
// 		PolicyQualifierInfo_policyQualifierId_oid_m_c,
// 	} policyQualifierId_choice;
// 	struct zcbor_string qualifier;
// };

// struct PolicyIdentifier_m_l_PolicyQualifierInfo_m_l
// {
// 	struct PolicyQualifierInfo PolicyQualifierInfo_m[1024];
// 	size_t PolicyQualifierInfo_m_count;
// };

// struct CertificatePolicies_PolicyIdentifier_m_l
// {
// 	struct PolicyIdentifier_r PolicyIdentifier_m;
// 	struct PolicyIdentifier_m_l_PolicyQualifierInfo_m_l PolicyQualifierInfo_m_l;
// 	bool PolicyQualifierInfo_m_l_present;
// };

// struct CertificatePolicies
// {
// 	struct CertificatePolicies_PolicyIdentifier_m_l PolicyIdentifier_m_l[1024];
// 	size_t PolicyIdentifier_m_l_count;
// };

// struct GeneralSubtrees
// {
// 	struct GeneralName GeneralName_m[1024];
// 	size_t GeneralName_m_count;
// };

// struct NameConstraints
// {
// 	union
// 	{
// 		struct GeneralSubtrees GeneralSubtrees_m;
// 	};
// 	enum
// 	{
// 		NameConstraints_permittedSubtrees_GeneralSubtrees_m_c,
// 		NameConstraints_permittedSubtrees_null_m_c,
// 	} permittedSubtrees_choice;
// 	union
// 	{
// 		struct GeneralSubtrees GeneralSubtrees_m;
// 	};
// 	enum
// 	{
// 		NameConstraints_excludedSubtrees_GeneralSubtrees_m_c,
// 		NameConstraints_excludedSubtrees_null_m_c,
// 	} excludedSubtrees_choice;
// };

// struct Attributes_r
// {
// 	union
// 	{
// 		struct
// 		{
// 			int32_t attributeTypesInt;
// 			struct zcbor_string text_m[1024];
// 			size_t text_m_count;
// 		};
// 		struct
// 		{
// 			struct zcbor_string attributeTypesOID;
// 			struct zcbor_string bytes_m[1024];
// 			size_t bytes_m_count;
// 		};
// 	};
// 	enum
// 	{
// 		Attributes_attributeTypesInt_l_c,
// 		Attributes_attributeTypesOID_l_c,
// 	} Attributes_choice;
// };

// struct SubjectDirectoryAttributes
// {
// 	struct Attributes_r Attributes_m[1024];
// 	size_t Attributes_m_count;
// };

// struct ASIdOrRange_r
// {
// 	union
// 	{
// 		uint32_t uint;
// 		struct
// 		{
// 			uint32_t min;
// 			uint32_t max;
// 		};
// 	};
// 	enum
// 	{
// 		ASIdOrRange_uint_c,
// 		ASIdOrRange_min_l_c,
// 	} ASIdOrRange_choice;
// };

// struct ASIdentifiers_r
// {
// 	union
// 	{
// 		struct
// 		{
// 			struct ASIdOrRange_r ASIdOrRange_m[1024];
// 			size_t ASIdOrRange_m_count;
// 		};
// 	};
// 	enum
// 	{
// 		ASIdentifiers_ASIdOrRange_m_l_c,
// 		ASIdentifiers_null_m_c,
// 	} ASIdentifiers_choice;
// };

// struct AddressPrefix
// {
// 	struct zcbor_string Address_m;
// 	uint32_t unusedBits;
// };

// struct AddressRange
// {
// 	struct zcbor_string min;
// 	struct zcbor_string max;
// };

// struct IPAddressOrRange_r
// {
// 	union
// 	{
// 		struct AddressPrefix AddressPrefix_m;
// 		struct AddressRange AddressRange_m;
// 	};
// 	enum
// 	{
// 		IPAddressOrRange_AddressPrefix_m_c,
// 		IPAddressOrRange_AddressRange_m_c,
// 	} IPAddressOrRange_choice;
// };

// struct IPAddressChoice_r
// {
// 	union
// 	{
// 		struct
// 		{
// 			struct IPAddressOrRange_r IPAddressOrRange_m[1024];
// 			size_t IPAddressOrRange_m_count;
// 		};
// 	};
// 	enum
// 	{
// 		IPAddressChoice_IPAddressOrRange_m_l_c,
// 		IPAddressChoice_null_m_c,
// 	} IPAddressChoice_choice;
// };

// struct IPAddressFamily
// {
// 	uint32_t AFI;
// 	struct IPAddressChoice_r IPAddressChoice_m;
// };

// struct IPAddrBlocks
// {
// 	struct IPAddressFamily IPAddressFamily_m[1024];
// 	size_t IPAddressFamily_m_count;
// };

// struct SignedCertificateTimestamp
// {
// 	struct zcbor_string logID;
// 	int32_t timestamp;
// 	struct AlgorithmIdentifier_r sigAlg;
// };

// struct SignedCertificateTimestamps
// {
// 	struct SignedCertificateTimestamp SignedCertificateTimestamp_m[1024];
// 	size_t SignedCertificateTimestamp_m_count;
// };