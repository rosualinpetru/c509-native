add_library(c509_structures STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/algid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/attr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/c509.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cert.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/csn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/csr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/name.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/oid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/priv.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/time.cpp)

target_include_directories(c509_structures
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)