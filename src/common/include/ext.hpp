// #ifndef __C509_EXTENSIONS_H
// #define __C509_EXTENSIONS_H

// #include <optional>

// #include "cbor.hpp"
// #include "definitions.hpp"
// #include "util.hpp"

// constexpr size_t MAX_PARMETER_BYTES = 4096; // WARNING

// struct Extension
// {
//     enum class Type
//     {
//         Int,
//         OID
//     } const type;

//     union
//     {
//         const uint8_t intId;
//         // TODO: Need to implement all extensions before being able to integrate them
//         struct OIDId
//         {
//             const OID oidId;
//             const std::optional<array<uint8_t, MAX_PARMETER_BYTES>> params;
//         } const oidWithParams;
//     };

//     struct Extensions
//     {
//         enum class Type
//         {
//             Int,
//             OID
//         } const type;

//         union
//         {
//             const uint8_t intId;
//             struct OIDId
//             {
//                 const OID oidId;
//                 const std::optional<array<uint8_t, MAX_PARMETER_BYTES>> params;
//             } const oidWithParams;
//         };
//     };

//     DECLARE_CBOR_CODEC(Extensions)

// #endif
// __C509_EXTENSIONS_H

// 	struct IntExtension
// 	{
// 		CBOR::Prelude::Int extensionID;
// 		CBOR::Prelude::Any attributeValue;
// 	};

// 	struct OIDExtension
// 	{
// 		CBOR::Prelude::BStr extensionID; // unwrapped OID
// 		CBOR::Prelude::Bool critical;
// 		CBOR::Prelude::Bytes attributeValue;
// 	};

// 	struct Extension
// 	{
// 		std::variant<IntExtension, OIDExtension> choice;
// 	};

// 	struct Extensions
// 	{
// 		std::variant<std::vector<Extension>,
// 					 CBOR::Prelude::Int>
// 			choice;
// 	};