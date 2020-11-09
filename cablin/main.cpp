#include <mukyu/cablin/core/program.hpp>

#include <stdexcept>
#include <iostream>

namespace mccore = mukyu::cablin::core;

int main(int argc, char** argv) {
    try {
        mccore::Program prog(argv[1]);
        return prog.execute({});
    } catch (const std::exception& ex) {
        throw;
    }
}