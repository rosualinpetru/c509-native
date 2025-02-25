set(liboqs_DIR ${liboqs_BINARY_DIR})
set(LIBOQS_INCLUDE_DIR ${liboqs_BINARY_DIR}/include)
add_library(OQS::oqs STATIC IMPORTED)
set_target_properties(OQS::oqs PROPERTIES
    IMPORTED_LOCATION ${liboqs_DIR}/lib/liboqs.a
    INTERFACE_INCLUDE_DIRECTORIES ${LIBOQS_INCLUDE_DIR}
)
