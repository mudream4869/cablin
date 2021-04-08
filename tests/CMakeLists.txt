cmake_minimum_required(VERSION 3.6.2)

add_subdirectory(third_party/googletest)

include_directories(third_party/googletest/googletest/include)

include_directories(../include/)

set(cablin_test_command_src
    "src/command/test_if.cpp"
    "src/command/test_scope.cpp"
    "src/command/test_while.cpp"
    "src/command/test_var.cpp")

set(cablin_test_expr_src
    "src/expr/test_const.cpp"
    "src/expr/test_unary_op.cpp")

set(cablin_test_function_src
    "src/function/test_functor.cpp"
    "src/function/test_node.cpp")

add_executable(unit_tests
    ${cablin_test_command_src}
    ${cablin_test_expr_src}
    ${cablin_test_function_src})

add_dependencies(unit_tests cablin)
target_link_libraries(unit_tests cablin gtest gtest_main)

add_test(NAME unit_tests
         COMMAND unit_tests) 
