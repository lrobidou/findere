cmake_minimum_required(VERSION 3.13.0)
project(qtf VERSION 0.1.0)

set(CONTACT "lucas.robidou@inria.fr")

set(CMAKE_CXX_STANDARD 17)  # TODO: find why this does not work if I overwrite CMAKE_CXX_COMPILER (even before)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror --std=c++17")  # I have to specify the standard version here...
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# thirdparty source directories
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

# thirdparty build directories
set(THIRDPARTY_BUILD_DIR ${PROJECT_BINARY_DIR}/thirdparty)

include_directories(SYSTEM thirdparty/libbf)
include_directories(SYSTEM thirdparty/json/include)
include_directories(SYSTEM thirdparty/cxxopts/include)
include_directories(SYSTEM thirdparty/robinHoodHashing/src/include)
include_directories(SYSTEM thirdparty/zstr/src)
include_directories(SYSTEM /usr/include)
# add libbf
add_subdirectory(thirdparty/libbf)

# add googletest
add_subdirectory(thirdparty/googletest)



# build src qtf
add_subdirectory(src)
add_subdirectory(tests)