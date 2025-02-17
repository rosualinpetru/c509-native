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

# zcbor 
# add_compile_definitions(ZCBOR_VERBOSE=1) # useful for debugging
add_git_submodule(${EXTERNAL_DIR}/zcbor)

# liboqs 
set(OQS_BUILD_ONLY_LIB ON)
set(OQS_MINIMAL_BUILD "SIG_ml_dsa_44;SIG_ml_dsa_65;SIG_dilithium_2")
set(OQS_USE_OPENSSL OFF)
# set(OQS_EMBEDDED_BUILD ON)
FetchContent_Declare(
    liboqs
    GIT_REPOSITORY https://github.com/open-quantum-safe/liboqs
    GIT_TAG 0.12.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(liboqs)

if(ENABLE_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.8.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

### Tasks

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
