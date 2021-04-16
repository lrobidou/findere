add_library(qtf_truth_lib truth.cpp)  # QTF library
add_library(qtf_utils_lib utils.cpp)  # QTF library
add_library(qtf_fileIndexer_lib FileIndexer.cpp utils.cpp)  # QTF library

add_executable(main test.cpp)

target_link_libraries(main qtf_truth_lib qtf_utils_lib qtf_fileIndexer_lib qtf_querier_lib bf)