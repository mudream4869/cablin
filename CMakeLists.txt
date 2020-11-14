cmake_minimum_required(VERSION 3.6.2)
project(mukyu_cablin)

find_package(yaml-cpp REQUIRED)

include_directories(${YAML_CPP_INCLUDE_DIRS})

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

set(cablin_core_src
    src/core/controller.cpp
    "src/core/program.cpp")

set(cablin_command_src
    "src/command/factory.cpp"
    "src/command/if.cpp"
    "src/command/block.cpp"
    "src/command/call.cpp"
    "src/command/var.cpp"
    "src/command/globalvar.cpp"
    "src/command/while.cpp"
    "src/command/assign.cpp")

set(cablin_function_src
    src/function/print.cpp
    src/function/node.cpp)

set(cablin_expr_src
    src/expr/call.cpp
    src/expr/getvar.cpp
    src/expr/factory.cpp)

set(cablin_package_src
    src/package/builtin_io.cpp
    src/package/builtin_op.cpp
    src/package/builtin_cast.cpp
    src/package/userdefine.cpp)

add_library(cablin
            ${cablin_core_src}
            ${cablin_command_src}
            ${cablin_function_src}
            ${cablin_package_src}
            ${cablin_expr_src})

target_link_libraries(cablin
                      ${YAML_CPP_LIBRARIES})

# ----------
# Interpreter

add_subdirectory(interpreter)

# ----------
# Unit Test

add_subdirectory(test)
