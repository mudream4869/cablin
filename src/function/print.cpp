#include <mukyu/cablin/function/print.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


namespace mukyu {
namespace cablin {
namespace function {


namespace mccore = mukyu::cablin::core;


namespace {


const std::string FUNCTION_PRINT_NAME = "print";


}


class FunctionPrint::Impl {
public:
    Impl() = default;
    ~Impl() = default;

    const std::string& getName() const {
        return FUNCTION_PRINT_NAME;
    }

    mccore::Value execute(mccore::Controller* controller,
                          std::vector<mccore::Value> params) {
        for (const auto& param : params) {
            switch (param.type()) {
            case mccore::ValueType::BOOL:
                if (param.as<bool>()) {
                    std::cout << "true\n";
                } else {
                    std::cout << "false\n";
                }
                break;
            case mccore::ValueType::INT:
                std::cout << param.as<int>() << "\n";
                break;
            case mccore::ValueType::STRING:
                std::cout << param.as<std::string>() << "\n";
                break;
            case mccore::ValueType::NONE:
                std::cout << "none\n";
                break;
            default:
                throw std::runtime_error(
                    "Impl::execute: " +
                    mccore::VALUETYPE_STR_MAP.at(param.type()) +
                    "type not support");
            }
        }
        return static_cast<int>(params.size());
    }
};

FunctionPrint::FunctionPrint() : impl_(std::make_unique<Impl>()) {
}

FunctionPrint::~FunctionPrint() = default;

const std::string& FunctionPrint::getName() const {
    return impl_->getName();
}

mccore::Value FunctionPrint::execute(mccore::Controller* controller,
                                     std::vector<mccore::Value> params) {
    return impl_->execute(controller, params);
}


}  // namespace function
}  // namespace cablin
}  // namespace mukyu