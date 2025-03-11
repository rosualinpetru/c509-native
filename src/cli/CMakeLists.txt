add_executable(c509_cli
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file/file_util.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/genpkey.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/req.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/bundle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cli.cpp
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
        c509_core
        brotlienc
        brotlidec
        brotlicommon
)