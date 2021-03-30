set(SDSL_LIB_DIR ${THIRDPARTY_DIR}/sdls-lite/lib)
set(SDSL_INCLUDE ${THIRDPARTY_DIR}/sdls-lite/include)
set(GDIR ${THIRDPARTY_DIR}/googletest)
set(GINCLUDE ${GDIR}/googletest/include)
set(GLIB_DIR ${GDIR}/src/googletest-build/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/)

file(GLOB TEST_FILES "test_*.cpp")
add_executable(QTF_tests "main.cpp" ${TEST_FILES})


# add_library(FileIndexer src/FileIndexer.cpp)  # QTF library

target_link_libraries(QTF_tests FileIndexer)   # -l flags for linking prog target

link_directories(${SDSL_LIB_DIR})
include_directories(${SDSL_INCLUDE})

target_include_directories(QTF_tests PUBLIC ${GINCLUDE})
target_link_directories(QTF_tests PUBLIC ${GLIB_DIR})# ${PROJECT_SOURCE_DIR}/bin/lib)
target_link_libraries(QTF_tests gtest gtest_main)