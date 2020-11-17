cmake_minimum_required(VERSION 3.6.2)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

include_directories(../include/)

set(cablin_test_command_src
    "src/command/test_if.cpp"
    "src/command/test_scope.cpp"
    "src/command/test_while.cpp"
    "src/command/test_var.cpp")

set(cablin_test_expr_src
    "src/expr/test_const.cpp")

set(cablin_test_function_src
    "src/function/test_functor.cpp"
    "src/function/test_node.cpp")

add_executable(test
    ${cablin_test_command_src}
    ${cablin_test_expr_src}
    ${cablin_test_function_src})

add_dependencies(test cablin)
target_link_libraries(test cablin ${GTEST_BOTH_LIBRARIES})
