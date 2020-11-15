#include <mukyu/cablin/core/script.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <stdexcept>
#include <iostream>

namespace mccore = mukyu::cablin::core;

int main(int argc, char** argv) {
    mccore::Script script(argv[1]);
    script.callFunction("hello_world", {});
    return 0;
}