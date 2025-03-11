add_library(c509_core STATIC
        src/key_gen.cpp
        src/csr_gen.cpp
        src/csr_verify.cpp
        src/csr_sign.cpp
        src/crl_gen.cpp
        src/crl_revoke.cpp
        src/id_mapper.cpp
)

target_include_directories(c509_core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(c509_core
        PUBLIC
        c509_structures
        c509_codec
        c509_crypto
)