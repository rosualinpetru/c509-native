add_library(zcbor STATIC
    ${CMAKE_CURRENT_LIST_DIR}/zcbor/src/zcbor_decode.c
    ${CMAKE_CURRENT_LIST_DIR}/zcbor/src/zcbor_encode.c
    ${CMAKE_CURRENT_LIST_DIR}/zcbor/src/zcbor_common.c
    ${CMAKE_CURRENT_LIST_DIR}/zcbor/src/zcbor_print.c
)

target_include_directories(zcbor
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/zcbor/include>
    $<INSTALL_INTERFACE:include>
)