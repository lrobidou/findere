include_directories("/usr/local/include")

link_directories("/usr/local/lib")



add_executable(main test.cpp)

target_link_libraries(main qtf_truth_lib qtf_utils_lib qtf_fileIndexer_lib bf)