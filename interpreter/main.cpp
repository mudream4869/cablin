#include <mukyu/cablin/core/script.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <stdexcept>
#include <iostream>

namespace mccore = mukyu::cablin::core;

int main(int argc, char** argv) {
    try {
        mccore::Script script(".");
        script.addFile("main", argv[1]);
        auto result = script.callFunction("main", "main", {});

        if (result.type() == mccore::ValueType::NONE) {
            return 0;
        }

        return result.as<int>();
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