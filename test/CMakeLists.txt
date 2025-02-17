include(Catch)

add_executable(UnitTestsCodec
    test_csn_codec.cpp
    test_oid_codec.cpp)

target_link_libraries(UnitTestsCodec PUBLIC c509_codec)
target_link_libraries(UnitTestsCodec PRIVATE Catch2::Catch2WithMain)

target_include_directories(UnitTestsCodec
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/codec/src
)

catch_discover_tests("UnitTestsCodec")
