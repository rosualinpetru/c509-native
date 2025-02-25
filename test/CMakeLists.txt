include(Catch)

add_executable(UnitTestsCodec
    test_csn_codec.cpp
    test_oid_codec.cpp
    test_algid_codec.cpp
    test_attr_codec.cpp
    test_time_codec.cpp
    test_name_codec.cpp
    test_ext_codec.cpp
    test_crypto.cpp)

target_link_libraries(UnitTestsCodec PUBLIC c509_codec OpenSSL::Crypto oqsprovider)
target_link_libraries(UnitTestsCodec PRIVATE Catch2::Catch2WithMain)

target_include_directories(UnitTestsCodec
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/codec/src
)

catch_discover_tests(UnitTestsCodec)