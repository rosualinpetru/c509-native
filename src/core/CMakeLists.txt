add_library(c509_core STATIC
        src/csr/gen.cpp
        src/util/algid_mapper.cpp
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