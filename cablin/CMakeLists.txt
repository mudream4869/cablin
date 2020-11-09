cmake_minimum_required(VERSION 3.6.2)

enable_testing()

include_directories(../include/)

add_executable(cabl main.cpp)
add_dependencies(cabl cablin)
target_link_libraries(cabl cablin ${GTEST_BOTH_LIBRARIES})
