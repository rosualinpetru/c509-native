add_library(c509_codec STATIC
    src/c509_decode.cpp
    src/c509_encode.cpp
)

target_include_directories(c509_codec
    PUBLIC
    ./include
)

target_link_libraries(c509_codec
    PUBLIC
    c509_common
    PRIVATE
    zcbor
)
