#pragma once

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>
#include <mukyu/cablin/core/error.hpp>

#include <functional>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace function {


enum class UnaryOperatorType {
    NOT,
};

const std::unordered_map<UnaryOperatorType, std::string>
    FUNCTION_UNARY_OPERATOR_NAME_MAP = {
        {UnaryOperatorType::NOT, "not"},
};

using UnaryOperatorFunctionType = std::function<mukyu::cablin::core::Value(
    const mukyu::cablin::core::Value&)>;

const std::unordered_map<UnaryOperatorType, UnaryOperatorFunctionType>
    FUNCTION_UNARY_OPERATOR_FUNC_MAP = {
        {UnaryOperatorType::NOT, mukyu::cablin::core::operator!}, };

template <UnaryOperatorType type>
class FunctionUnaryOperator : public mukyu::cablin::core::Function {
public:
    FunctionUnaryOperator()
        : name_(FUNCTION_UNARY_OPERATOR_NAME_MAP.at(type)),
          func_(FUNCTION_UNARY_OPERATOR_FUNC_MAP.at(type)) {
    }

    ~FunctionUnaryOperator() = default;

    const std::string& getName() const {
        return name_;
    }

    mukyu::cablin::core::Value execute(mukyu::cablin::core::Controller*,
                                       mukyu::cablin::core::ValueList params) {
        if (params.size() != 1) {
            throw mukyu::cablin::core::CablinRuntimeException(
                "FunctionUnaryOperator<" + name_ +
                ">::execute: |params| should be 1");
        }

        return func_(params[0]);
    }

private:
    std::string name_;
    UnaryOperatorFunctionType func_;
};

using FunctionOperatorNot = FunctionUnaryOperator<UnaryOperatorType::NOT>;


}  // namespace function
}  // namespace cablin
}  // namespace mukyu