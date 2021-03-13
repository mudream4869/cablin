cmake_minimum_required(VERSION 3.6.2)
project(mukyu_cablin)

if (MSVC)
  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG})
  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL     ${CMAKE_CXX_FLAGS_MINSIZEREL})
  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE})
  string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
  add_definitions("/wd4267 /wd4244 /wd4305 /Zc:strictStrings /utf-8")
endif()

add_subdirectory(third_party/yaml-cpp)
include_directories(third_party/yaml-cpp/include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

set(cablin_core_src
    src/core/controller.cpp
    "src/core/script.cpp")

set(cablin_common_src
    src/common/yamlutil.cpp)

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

set(cablin_config_src
    src/config/yamlconfig.cpp)

set(cablin_package_src
    src/package/builtin_io.cpp
    src/package/builtin_op.cpp
    src/package/builtin_cast.cpp
    src/package/factory.cpp
    src/package/userdefine.cpp)

add_library(cablin
            ${cablin_core_src}
            ${cablin_command_src}
            ${cablin_common_src}
            ${cablin_config_src}
            ${cablin_function_src}
            ${cablin_package_src}
            ${cablin_expr_src})

target_link_libraries(cablin
                      PRIVATE
                      yaml-cpp
                      Threads::Threads)

# ----------
# Installation

install(TARGETS cablin
        DESTINATION lib
        COMPONENT cablin)

install(DIRECTORY include/mukyu
        DESTINATION include
        COMPONENT cablin)

# ----------
# Interpreter

add_subdirectory(interpreter)

# ----------
# Example

add_subdirectory(example)

# ----------
# Unit Test

add_subdirectory(tests)

# ----------
# Archive support

set(CPACK_ARCHIVE_FILE_NAME "mukyu-cablin")
set(CPACK_ARCHIVE_COMPONENT_INSTALL 1)
set(CPACK_COMPONENTS_ALL cablin)

set(CPACK_GENERATOR "ZIP")

include(CPack)
