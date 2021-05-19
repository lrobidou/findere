add_executable(paper mainPaper.cpp)
add_executable(index index.cpp)
add_executable(query query.cpp)

add_subdirectory(libraries)

target_link_libraries(paper qtf_utils_lib qtf_querier_lib libbf_static z)
target_link_libraries(index qtf_utils_lib qtf_querier_lib libbf_static z)
target_link_libraries(query qtf_utils_lib qtf_querier_lib libbf_static z)