cmake_minimum_required(VERSION 3.13.0)
project(qtf VERSION 0.1.0)

set(CONTACT "lucas.robidou@inria.fr")

set(CMAKE_CXX_STANDARD 17)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# thirdparty source directories
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

# thirdparty build directories
set(THIRDPARTY_BUILD_DIR ${PROJECT_BINARY_DIR}/thirdparty)

include_directories(SYSTEM thirdparty/json/include)
include_directories(SYSTEM thirdparty/cxxopts/include)

add_library(qtf_truth_lib src/truth.cpp src/utils.cpp)  # QTF library
add_library(qtf_utils_lib src/utils.cpp)  # QTF library
add_library(qtf_fileIndexer_lib src/FileIndexer.cpp src/utils.cpp src/truth.cpp)  # QTF library
add_library(qtf_querier_lib src/querier.cpp)# src/utils.cpp src/truth.cpp)  # QTF library
add_library(qtf_similarity_lib src/similarity.cpp)# src/utils.cpp src/truth.cpp)  # QTF library

# build src qtf
add_subdirectory(src)
add_subdirectory(tests)