file(GLOB TEST_FILES "test_*.cpp")
add_executable(QTF_tests "main.cpp" ${TEST_FILES})


target_link_libraries(QTF_tests gtest gtest_main libbf_static z pthread)
