cmake_minimum_required(VERSION 3.6.2)

include_directories(../include/)

add_executable(example1 example1.cpp)
add_dependencies(example1 cablin)
target_link_libraries(example1 cablin)

add_executable(example2 example2.cpp)
add_dependencies(example2 cablin)
target_link_libraries(example2 cablin)

install(PROGRAMS example1
        DESTINATION bin
        COMPONENT cablin_example)

install(PROGRAMS example2
        DESTINATION bin
        COMPONENT cablin_example)
