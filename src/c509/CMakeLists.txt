add_library(c509 STATIC
    src/c509.cpp
)

target_include_directories(c509
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(c509
    PUBLIC
    c509_common
    PRIVATE
    c509_crypto
    c509_codec
)
