#include <mukyu/cablin/core/script.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <stdexcept>
#include <iostream>

namespace mccore = mukyu::cablin::core;

int main(int argc, char** argv) {
    try {
        mccore::Script script(argv[1]);
        return script.main({});
    } catch (const mccore::CablinParsingException& ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << "Line: " << ex.line << ", Column: " << ex.column
                  << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}