cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(nestest "${CMAKE_CURRENT_LIST_DIR}/test.cpp")
target_link_libraries(nestest nesbit)