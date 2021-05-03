add_executable(main main.cpp)
add_subdirectory(libraries)
target_link_libraries(main qtf_utils_lib qtf_querier_lib libbf_static z)
