#ifndef C509_CBOR_CODEC_ERRORS_H
#define C509_CBOR_CODEC_ERRORS_H

// CSN
#define C509_ERR_CSN_ENC_BSTR           509'000'000

#define C509_ERR_CSN_DEC_BSTR           509'000'100
#define C509_ERR_CSN_DEC_INVALID_LENGTH 509'000'101
#define C509_ERR_CSN_DEC_BUFFER_ERROR   509'000'102

// OID
#define C509_ERR_OID_ENC_BSTR           509'001'000
#define C509_ERR_OID_ENC_INVALID_LENGTH 509'001'001

#define C509_ERR_OID_DEC_BSTR           509'001'100
#define C509_ERR_OID_DEC_INVALID_LENGTH 509'001'101
#define C509_ERR_OID_DEC_MALFORMED      509'001'102

// ALGID
#define C509_ERR_ALGID_ENC_UNSUPPORTED_TYPE 509'002'000
#define C509_ERR_ALGID_ENC_INT              509'002'001
#define C509_ERR_ALGID_ENC_LIST_START       509'002'002
#define C509_ERR_ALGID_ENC_LIST_END         509'002'003
#define C509_ERR_ALGID_ENC_OID              509'002'004
#define C509_ERR_ALGID_ENC_PARAMS           509'002'005

#define C509_ERR_ALGID_DEC_LIST_START       509'002'100
#define C509_ERR_ALGID_DEC_LIST_END         509'002'101
#define C509_ERR_ALGID_DEC_OID              509'002'102
#define C509_ERR_ALGID_DEC_PARAMS           509'002'103
#define C509_ERR_ALGID_DEC_INVALID_LENGTH   509'002'104
#define C509_ERR_ALGID_DEC_BUFFER_ERROR     509'002'105

// ATTR
#define C509_ERR_ATTR_ENC_UNSUPPORTED_TYPE 509'003'000
#define C509_ERR_ATTR_ENC_INT              509'003'001
#define C509_ERR_ATTR_ENC_OID              509'003'002
#define C509_ERR_ATTR_ENC_TSTR             509'003'003
#define C509_ERR_ATTR_ENC_BSTR             509'003'004

#define C509_ERR_ATTR_DEC_OID              509'003'100
#define C509_ERR_ATTR_DEC_TSTR             509'003'101
#define C509_ERR_ATTR_DEC_BSTR             509'003'102
#define C509_ERR_ATTR_DEC_INVALID_LENGTH   509'003'103
#define C509_ERR_ATTR_DEC_BUFFER_ERROR     509'003'104

// TIME
#define C509_ERR_TIME_ENC_INT 509'004'000

#define C509_ERR_TIME_DEC_INT 509'004'100

// NAME
#define C509_ERR_NAME_ENC_UNSUPPORTED_TYPE 509'005'000
#define C509_ERR_NAME_ENC_BSTR             509'005'001
#define C509_ERR_NAME_ENC_TSTR             509'005'002
#define C509_ERR_NAME_ENC_ATTR             509'005'003
#define C509_ERR_NAME_ENC_LIST_START       509'005'004
#define C509_ERR_NAME_ENC_LIST_END         509'005'005

#define C509_ERR_NAME_DEC_ATTR             509'005'100
#define C509_ERR_NAME_DEC_LIST_START       509'005'101
#define C509_ERR_NAME_DEC_LIST_END         509'005'102
#define C509_ERR_NAME_DEC_INVALID_LENGTH   509'005'103
#define C509_ERR_NAME_DEC_BUFFER_ERROR     509'005'104

// EXT
#define C509_ERR_EXT_ENC_UNSUPPORTED_TYPE  509'006'000
#define C509_ERR_EXT_ENC_OID               509'006'001
#define C509_ERR_EXT_ENC_CRITICAL          509'006'002
#define C509_ERR_EXT_ENC_BSTR_VALUE        509'006'003

#define C509_ERR_EXT_DEC_OID               509'006'100
#define C509_ERR_EXT_DEC_CRITICAL          509'006'101
#define C509_ERR_EXT_DEC_BSTR_VALUE        509'006'102
#define C509_ERR_EXT_DEC_INVALID_LENGTH    509'006'103
#define C509_ERR_EXT_DEC_BUFFER_ERROR      509'006'104

#define C509_ERR_EXTS_ENC_UNSUPPORTED_TYPE 509'007'000
#define C509_ERR_EXTS_ENC_MKU              509'007'001
#define C509_ERR_EXTS_ENC_EXT              509'007'002
#define C509_ERR_EXTS_ENC_LIST_START       509'007'003
#define C509_ERR_EXTS_ENC_LIST_END         509'007'004

#define C509_ERR_EXTS_DEC_EXT              509'007'000
#define C509_ERR_EXTS_DEC_LIST_START       509'007'001
#define C509_ERR_EXTS_DEC_LIST_END         509'007'002

// TBS CERTIFICATE
#define C509_ERR_TBSCERT_ENC_CERT_TYPE           509'008'000
#define C509_ERR_TBSCERT_ENC_SERIAL_NUMBER       509'008'001
#define C509_ERR_TBSCERT_ENC_ISSUER_SIG_ALG      509'008'002
#define C509_ERR_TBSCERT_ENC_ISSUER              509'008'003
#define C509_ERR_TBSCERT_ENC_ISSUER_NIL          509'008'004
#define C509_ERR_TBSCERT_ENC_VALIDITY_NOT_BEFORE 509'008'005
#define C509_ERR_TBSCERT_ENC_VALIDITY_NOT_AFTER  509'008'006
#define C509_ERR_TBSCERT_ENC_VALIDITY_NIL        509'008'007
#define C509_ERR_TBSCERT_ENC_SUBJECT             509'008'008
#define C509_ERR_TBSCERT_ENC_SUBJ_PUBKEY_ALG     509'008'009
#define C509_ERR_TBSCERT_ENC_SUBJ_PUBKEY         509'008'010
#define C509_ERR_TBSCERT_ENC_EXTENSIONS          509'008'011

#define C509_ERR_TBSCERT_DEC_CERT_TYPE           509'008'100
#define C509_ERR_TBSCERT_DEC_SERIAL_NUMBER       509'008'101
#define C509_ERR_TBSCERT_DEC_ISSUER_SIG_ALG      509'008'102
#define C509_ERR_TBSCERT_DEC_ISSUER              509'008'103
#define C509_ERR_TBSCERT_DEC_VALIDITY_NOT_BEFORE 509'008'104
#define C509_ERR_TBSCERT_DEC_VALIDITY_NOT_AFTER  509'008'105
#define C509_ERR_TBSCERT_DEC_SUBJECT             509'008'106
#define C509_ERR_TBSCERT_DEC_SUBJ_PUBKEY_ALG     509'008'107
#define C509_ERR_TBSCERT_DEC_SUBJ_PUBKEY         509'008'108
#define C509_ERR_TBSCERT_DEC_EXTENSIONS          509'008'109

// SIG
#define C509_ERR_SIG_ENC_BSTR           509'009'000

#define C509_ERR_SIG_DEC_BSTR           509'009'100
#define C509_ERR_SIG_DEC_INVALID_LENGTH 509'009'101
#define C509_ERR_SIG_DEC_BUFFER_ERROR   509'009'102

// PK
#define C509_ERR_PK_ENC_BSTR           509'010'000

#define C509_ERR_PK_DEC_BSTR           509'010'100
#define C509_ERR_PK_DEC_INVALID_LENGTH 509'010'101
#define C509_ERR_PK_DEC_BUFFER_ERROR   509'010'102

// CSR

#define CSR_ERR_TBSCERTREQ_ENC_TYPE          509'011'000
#define CSR_ERR_TBSCERTREQ_ENC_SIG_ALG       509'011'001
#define CSR_ERR_TBSCERTREQ_ENC_SUBJECT       509'011'002
#define CSR_ERR_TBSCERTREQ_ENC_PUBKEY_ALG    509'011'003
#define CSR_ERR_TBSCERTREQ_ENC_PUBKEY        509'011'004
#define CSR_ERR_TBSCERTREQ_ENC_EXTENSIONS    509'011'005

#define CSR_ERR_TBSCERTREQ_DEC_TYPE          509'011'100
#define CSR_ERR_TBSCERTREQ_DEC_SIG_ALG       509'011'101
#define CSR_ERR_TBSCERTREQ_DEC_SUBJECT       509'011'102
#define CSR_ERR_TBSCERTREQ_DEC_PUBKEY_ALG    509'011'103
#define CSR_ERR_TBSCERTREQ_DEC_PUBKEY        509'011'104
#define CSR_ERR_TBSCERTREQ_DEC_EXTENSIONS    509'011'105

#define CSR_ERR_REQ_ENC_TBS           509'012'000
#define CSR_ERR_REQ_ENC_SIG           509'012'001
#define CSR_ERR_REQ_ENC_LIST_START    509'012'002
#define CSR_ERR_REQ_ENC_LIST_END      509'012'003

#define CSR_ERR_REQ_DEC_TBS           509'012'100
#define CSR_ERR_REQ_DEC_SIG           509'012'101
#define CSR_ERR_REQ_DEC_LIST_START    509'012'102
#define CSR_ERR_REQ_DEC_LIST_END      509'012'103

// CRL
#define CRL_ERR_RVCERT_ENC_CSN  509'013'000
#define CRL_ERR_RVCERT_ENC_DATE 509'013'001
#define CRL_ERR_RVCERT_ENC_EXTS 509'013'002

#define CRL_ERR_RVCERT_DEC_CSN  509'013'100
#define CRL_ERR_RVCERT_DEC_DATE 509'013'101
#define CRL_ERR_RVCERT_DEC_EXTS 509'013'102

#define CRL_ERR_TBSCERTREVLIST_ENC_TYPE                509'014'000
#define CRL_ERR_TBSCERTREVLIST_ENC_ISSUER              509'014'001
#define CRL_ERR_TBSCERTREVLIST_ENC_THISUPDATE          509'014'002
#define CRL_ERR_TBSCERTREVLIST_ENC_NEXTUPDATE          509'014'003
#define CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERTS_START  509'014'004
#define CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERTS_END    509'014'005
#define CRL_ERR_TBSCERTREVLIST_ENC_REVOKEDCERT         509'014'006
#define CRL_ERR_TBSCERTREVLIST_ENC_EXTENSIONS          509'014'007
#define CRL_ERR_TBSCERTREVLIST_ENC_SIG_ALG             509'014'008

#define CRL_ERR_TBSCERTREVLIST_DEC_TYPE                509'014'100
#define CRL_ERR_TBSCERTREVLIST_DEC_ISSUER              509'014'101
#define CRL_ERR_TBSCERTREVLIST_DEC_THISUPDATE          509'014'102
#define CRL_ERR_TBSCERTREVLIST_DEC_NEXTUPDATE          509'014'103
#define CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERTS_START  509'014'104
#define CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERTS_END    509'014'105
#define CRL_ERR_TBSCERTREVLIST_DEC_REVOKEDCERT         509'014'106
#define CRL_ERR_TBSCERTREVLIST_DEC_BUFFER_ERROR        509'014'107
#define CRL_ERR_TBSCERTREVLIST_DEC_EXTENSIONS          509'014'108
#define CRL_ERR_TBSCERTREVLIST_DEC_SIG_ALG             509'014'109


// PRIV
#define C509_ERR_PRIV_ENC_BSTR           509'018'000

#define C509_ERR_PRIV_DEC_BSTR           509'018'100
#define C509_ERR_PRIV_DEC_INVALID_LENGTH 509'018'101
#define C509_ERR_PRIV_DEC_BUFFER_ERROR   509'018'102

#define C509_ERR_PRIV_INFO_ENC_PK           509'019'000
#define C509_ERR_PRIV_INFO_ENC_PRIV         509'019'001
#define C509_ERR_PRIV_INFO_ENC_LIST_START   509'019'002
#define C509_ERR_PRIV_INFO_ENC_LIST_END     509'019'003

#define C509_ERR_PRIV_INFO_DEC_PK           509'019'100
#define C509_ERR_PRIV_INFO_DEC_PRIV         509'019'101
#define C509_ERR_PRIV_INFO_DEC_LIST_START   509'019'102
#define C509_ERR_PRIV_INFO_DEC_LIST_END     509'019'103

#define C509_ERR_PRIVK_ENC_ALG_ID         509'020'000
#define C509_ERR_PRIVK_ENC_INFO           509'020'001
#define C509_ERR_PRIVK_ENC_LIST_START     509'020'002
#define C509_ERR_PRIVK_ENC_LIST_END       509'020'003

#define C509_ERR_PRIVK_DEC_ALG_ID         509'020'100
#define C509_ERR_PRIVK_DEC_INFO           509'020'101
#define C509_ERR_PRIVK_DEC_LIST_START     509'020'102
#define C509_ERR_PRIVK_DEC_LIST_END       509'020'103

#define C509_ERR_C509PEM_ENC_PRIVK          509'021'000
#define C509_ERR_C509PEM_ENC_COSEC509       509'021'001
#define C509_ERR_C509PEM_ENC_LIST_START     509'021'002
#define C509_ERR_C509PEM_ENC_LIST_END       509'021'003
#define C509_ERR_C509PEM_ENC_NIL            509'021'004

#define C509_ERR_C509PEM_DEC_PRIVK          509'021'100
#define C509_ERR_C509PEM_DEC_COSEC509       509'021'101
#define C509_ERR_C509PEM_DEC_LIST_START     509'021'102
#define C509_ERR_C509PEM_DEC_LIST_END       509'021'103

// COSE_C509
#define C509_ERR_COSE_ENC_EMPTY          509'022'000
#define C509_ERR_COSE_ENC_C509           509'022'001
#define C509_ERR_COSE_ENC_LIST_START     509'022'002
#define C509_ERR_COSE_ENC_LIST_END       509'022'003

#define C509_ERR_COSE_DEC_C509           509'022'100
#define C509_ERR_COSE_DEC_LIST_START     509'022'101
#define C509_ERR_COSE_DEC_LIST_END       509'022'102

#endif // C509_CBOR_CODEC_ERRORS_H
