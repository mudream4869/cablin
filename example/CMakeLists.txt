cmake_minimum_required(VERSION 3.6.2)

include_directories(../include/)

add_executable(example main.cpp)
add_dependencies(example cablin)
target_link_libraries(example cablin)
