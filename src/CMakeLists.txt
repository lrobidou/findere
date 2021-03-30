# file(GLOB qtf_howde_lib_src
#      "../thirdparty/HowDeSBT/bloom_filter.cc"
#      "../thirdparty/HowDeSBT/bit_vector.cc"
#      "../thirdparty/HowDeSBT/bit_vector.h"
#      "../thirdparty/HowDeSBT/utilities.cc"
#      "../thirdparty/HowDeSBT/bit_utilities.cc"
#      "../thirdparty/HowDeSBT/file_manager.cc"
# )
include_directories("/usr/local/include")

link_directories("/usr/local/lib")

add_library(qtf_truth_lib truth.cpp)  # QTF library
add_library(qtf_utils_lib utils.cpp)  # QTF library
add_library(qtf_fileIndexer_lib FileIndexer.cpp utils.cpp)  # QTF library

add_executable(main test.cpp)

target_link_libraries(main qtf_truth_lib qtf_utils_lib qtf_fileIndexer_lib  bf)