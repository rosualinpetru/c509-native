add_executable(c509_cli ${CMAKE_CURRENT_SOURCE_DIR}/src/cli.cpp)

target_link_libraries(c509_cli
        PRIVATE
        c509_structures
        c509_codec
        c509_crypto
        c509_core
)