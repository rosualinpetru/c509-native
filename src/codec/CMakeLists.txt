add_library(c509_codec STATIC
    src/c509_codec.cpp
    src/cert_codec.cpp
    src/csn_codec.cpp
    src/sig_codec.cpp
    src/tbscert_codec.cpp
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
