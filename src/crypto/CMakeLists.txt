add_library(c509_crypto STATIC
    src/crypto.cpp
)

target_include_directories(c509_crypto
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(c509_crypto
    PUBLIC
    OpenSSL::Crypto
    oqsprovider
)