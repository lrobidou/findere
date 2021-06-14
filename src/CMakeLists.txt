add_executable(index index.cpp)
add_executable(query query.cpp)

target_link_libraries(index libbf_static z)
target_link_libraries(query libbf_static z)