include_directories("/usr/local/include")
link_directories("/usr/local/lib")


file(GLOB TEST_FILES "test_*.cpp")
add_executable(QTF_tests "main.cpp" ${TEST_FILES})



target_link_libraries(QTF_tests gtest gtest_main qtf_truth_lib qtf_utils_lib qtf_fileIndexer_lib bf pthread)