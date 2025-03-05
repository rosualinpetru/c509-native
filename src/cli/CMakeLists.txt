add_executable(c509_cli
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cli.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/handle_genpkey.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/file_util.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/parser.hpp
)


target_include_directories(c509_cli
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(c509_cli
        PRIVATE
        argparse
        c509_structures
        c509_codec
        c509_crypto
        c509_core
)