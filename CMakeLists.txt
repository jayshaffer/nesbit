cmake_minimum_required(VERSION 3.12)
project(nesbit)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(src)
add_subdirectory(test)

add_executable(main "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp")
target_link_libraries(main nesbit)