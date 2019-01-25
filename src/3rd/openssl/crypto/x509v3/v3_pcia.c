
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/x509v3.h>

ASN1_SEQUENCE(PROXY_POLICY) =
        {
        ASN1_SIMPLE(PROXY_POLICY,policyLanguage,ASN1_OBJECT),
        ASN1_OPT(PROXY_POLICY,policy,ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(PROXY_POLICY)

IMPLEMENT_ASN1_FUNCTIONS(PROXY_POLICY)

ASN1_SEQUENCE(PROXY_CERT_INFO_EXTENSION) =
        {
        ASN1_OPT(PROXY_CERT_INFO_EXTENSION,pcPathLengthConstraint,ASN1_INTEGER),
        ASN1_SIMPLE(PROXY_CERT_INFO_EXTENSION,proxyPolicy,PROXY_POLICY)
} ASN1_SEQUENCE_END(PROXY_CERT_INFO_EXTENSION)

IMPLEMENT_ASN1_FUNCTIONS(PROXY_CERT_INFO_EXTENSION)