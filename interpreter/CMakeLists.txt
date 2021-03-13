cmake_minimum_required(VERSION 3.6.2)

include_directories(../include/)

add_executable(interpreter main.cpp)
add_dependencies(interpreter cablin)
target_link_libraries(interpreter cablin)

install(PROGRAMS interpreter
        DESTINATION bin
        COMPONENT cablin_interpreter)
