file(GLOB TEST_FILES "test_*.cpp")
add_executable(QTF_tests "main.cpp" ${TEST_FILES})



target_link_libraries(QTF_tests gtest gtest_main qtf_truth_lib qtf_utils_lib qtf_indexer_lib qtf_similarity_lib qtf_evaluation_lib bf pthread)