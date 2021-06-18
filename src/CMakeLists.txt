add_executable(index index.cpp)
add_executable(query query.cpp)
add_executable(loop loopOverBits.cpp)

target_link_libraries(index libbf_static z)
target_link_libraries(query libbf_static z)
target_link_libraries(loop libbf_static z)