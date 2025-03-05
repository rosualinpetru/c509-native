cmake_minimum_required(VERSION 3.28)

project(c509-native VERSION 1.0.0 LANGUAGES C CXX)

### Global CMake variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Variables
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resource)

### Options
option(ENABLE_GEN_ZCBOR_CODEC "Generate encoders and decoders." OFF)
option(ENABLE_TESTING "Enable a Unit Testing build." ON)

### Modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

include(AddGitSubmodule)
include(FetchContent)
include(Docs)

### External libraries
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse
        GIT_TAG v3.2
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(argparse)

# zcbor 
# add_compile_definitions(ZCBOR_VERBOSE=1) # useful for debugging
add_compile_definitions(ZCBOR_CANONICAL=1)
add_git_submodule(${EXTERNAL_DIR}/zcbor)

# openssl
find_package(OpenSSL 3.0 REQUIRED)

# liboqs 
set(OQS_BUILD_ONLY_LIB ON)
set(OQS_MINIMAL_BUILD "SIG_ml_dsa_44;SIG_ml_dsa_65;SIG_ml_dsa_87")
# set(OQS_EMBEDDED_BUILD ON)
FetchContent_Declare(
    liboqs
    GIT_REPOSITORY https://github.com/open-quantum-safe/liboqs
    GIT_TAG 0.12.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(liboqs)

# oqs-provider
cmake_policy(SET CMP0077 NEW)

set(OQS_PROVIDER_BUILD_STATIC ON CACHE BOOL "Build OQS provider as a static library")
FetchContent_Declare(
    oqsprovider
    GIT_REPOSITORY https://github.com/open-quantum-safe/oqs-provider
    GIT_TAG 0.8.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(oqsprovider)

### Tasks

if(ENABLE_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.8.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

# Code generation
if(ENABLE_GEN_ZCBOR_CODEC)
    include(GenCodec)
    generate_cddl_codec(${RESOURCE_DIR}/c509.cddl)
endif()

### Subdirectories
add_subdirectory(external)
add_subdirectory(src)
if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

### Install

# install(
#     TARGETS c509
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib)
