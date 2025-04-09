include(Catch)

add_executable(c509_tests
        test_csn_codec.cpp
        test_oid_codec.cpp
        test_algid_codec.cpp
        test_attr_codec.cpp
        test_time_codec.cpp
        test_name_codec.cpp
        test_ext_codec.cpp
        create_dummy_cert.cpp
)

target_link_libraries(c509_tests PUBLIC c509_codec c509_crypto c509_core)
target_link_libraries(c509_tests PRIVATE Catch2::Catch2WithMain)

target_include_directories(c509_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/codec/src
)

catch_discover_tests(c509_tests)