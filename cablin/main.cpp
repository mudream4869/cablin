#include <mukyu/cablin/core/program.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <stdexcept>
#include <iostream>

namespace mccore = mukyu::cablin::core;

int main(int argc, char** argv) {
    try {
        mccore::Program prog(argv[1]);
        return prog.execute({});
    } catch (const mccore::CablinParsingException& ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << "Line: " << ex.line << ", Column: " << ex.column
                  << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}