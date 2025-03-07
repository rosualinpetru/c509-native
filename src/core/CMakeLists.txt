add_library(c509_core STATIC
        src/gen_csr.cpp
        src/keygen.cpp
        src/verify_csr.cpp
        src/sign_csr.cpp
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