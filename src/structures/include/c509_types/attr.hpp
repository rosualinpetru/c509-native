#ifndef C509_ATTRIBUTE_H
#define C509_ATTRIBUTE_H

#include <cstdint>
#include <string>

#include "structures.hpp"

#include "oid.hpp"


/*
https://datatracker.ietf.org/doc/html/rfc5280#appendix-A.1

-- Upper Bounds
ub-name INTEGER ::= 32768
ub-common-name INTEGER ::= 64
ub-locality-name INTEGER ::= 128
ub-state-name INTEGER ::= 128
ub-organization-name INTEGER ::= 64
ub-organizational-unit-name INTEGER ::= 64
ub-title INTEGER ::= 64
ub-serial-number INTEGER ::= 64
ub-match INTEGER ::= 128
ub-emailaddress-length INTEGER ::= 255
ub-common-name-length INTEGER ::= 64
ub-country-name-alpha-length INTEGER ::= 2
ub-country-name-numeric-length INTEGER ::= 3
ub-domain-defined-attributes INTEGER ::= 4
ub-domain-defined-attribute-type-length INTEGER ::= 8
ub-domain-defined-attribute-value-length INTEGER ::= 128
ub-domain-name-length INTEGER ::= 16
ub-extension-attributes INTEGER ::= 256
ub-e163-4-number-length INTEGER ::= 15
ub-e163-4-sub-address-length INTEGER ::= 40
ub-generation-qualifier-length INTEGER ::= 3
ub-given-name-length INTEGER ::= 16
ub-initials-length INTEGER ::= 5
ub-integer-options INTEGER ::= 256
ub-numeric-user-id-length INTEGER ::= 32
ub-organization-name-length INTEGER ::= 64
ub-organizational-unit-name-length INTEGER ::= 32
ub-organizational-units INTEGER ::= 4
ub-pds-name-length INTEGER ::= 16
ub-pds-parameter-length INTEGER ::= 30
ub-pds-physical-address-lines INTEGER ::= 6
ub-postal-code-length INTEGER ::= 16
ub-pseudonym INTEGER ::= 128
ub-surname-length INTEGER ::= 40
ub-terminal-id-length INTEGER ::= 24
ub-unformatted-address-length INTEGER ::= 180
ub-x121-address-length INTEGER ::= 16

Empirically, by enforcing different sizes, 64 is a reasonable option.
*/
#define MAX_ATTRIBUTE_VALUE_BYTES 64

namespace C509 {
    struct Attribute {
        enum class Type {
            Int,
            OID
        } type{};

        union {
            uint8_t integer{}; // int32_t if compatibility with re-encoded certs is needed
            OID oid;
        } attribute_type{};

        bounded_array<uint8_t, MAX_ATTRIBUTE_VALUE_BYTES> attribute_value;

        std::string to_string() const;
    };
}

#endif // C509_ATTRIBUTE_H
