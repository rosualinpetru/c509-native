include(Catch)

add_executable(UnitTestCodec test_codec.cpp)
target_link_libraries(UnitTestCodec PUBLIC c509_codec)
target_link_libraries(UnitTestCodec PRIVATE Catch2::Catch2WithMain)

catch_discover_tests("UnitTestCodec")
