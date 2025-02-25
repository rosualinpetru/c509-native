add_library(c509_codec STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/c509_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cert_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/csn_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tbscert_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/oid_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algid_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/attr_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/time_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/name_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ext_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sig/sig_codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pk/pk_codec.cpp
)

target_include_directories(c509_codec
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(c509_codec
    PUBLIC
    c509_common
    zcbor
)
