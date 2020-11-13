#pragma once

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <functional>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace function {


enum class BinaryOperatorType {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    AND,
    OR,
    EQUAL,
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,
};

const std::unordered_map<BinaryOperatorType, std::string>
    FUNCTION_BINARY_OPERATOR_NAME_MAP = {
        {BinaryOperatorType::PLUS, "plus"},
        {BinaryOperatorType::MINUS, "minus"},
        {BinaryOperatorType::MULTIPLY, "multiply"},
        {BinaryOperatorType::DIVIDE, "divide"},
        {BinaryOperatorType::MOD, "mod"},
        {BinaryOperatorType::AND, "and"},
        {BinaryOperatorType::OR, "or"},
        {BinaryOperatorType::EQUAL, "equal"},
        {BinaryOperatorType::LESS, "less"},
        {BinaryOperatorType::GREATER, "greater"},
        {BinaryOperatorType::LESS_EQUAL, "less_equal"},
        {BinaryOperatorType::GREATER_EQUAL, "greater_equal"},
};

using BinaryOperatorFunctionType = std::function<mukyu::cablin::core::Value(
    const mukyu::cablin::core::Value&, const mukyu::cablin::core::Value&)>;

const std::unordered_map<BinaryOperatorType, BinaryOperatorFunctionType>
    FUNCTION_BINARY_OPERATOR_FUNC_MAP = {
        {BinaryOperatorType::PLUS, mukyu::cablin::core::operator+ },
         {BinaryOperatorType::MINUS, mukyu::cablin::core::operator- },
          {BinaryOperatorType::MULTIPLY, mukyu::cablin::core::operator* },
           {BinaryOperatorType::DIVIDE, mukyu::cablin::core::operator/ },
            {BinaryOperatorType::MOD, mukyu::cablin::core::operator% },
             {BinaryOperatorType::AND, mukyu::cablin::core::operator&& },
              {BinaryOperatorType::OR, mukyu::cablin::core::operator|| },
               {BinaryOperatorType::EQUAL, mukyu::cablin::core::operator== },
                {BinaryOperatorType::LESS, mukyu::cablin::core::operator<},
                 {BinaryOperatorType::GREATER, mukyu::cablin::core::operator> },
                  {BinaryOperatorType::LESS_EQUAL,
                   mukyu::cablin::core::operator<= },
                   {BinaryOperatorType::GREATER_EQUAL,
                    mukyu::cablin::core::operator>= }, };

template <BinaryOperatorType type>
class FunctionBinaryOperator : public mukyu::cablin::core::Function {
public:
    FunctionBinaryOperator()
        : name_(FUNCTION_BINARY_OPERATOR_NAME_MAP.at(type)),
          func_(FUNCTION_BINARY_OPERATOR_FUNC_MAP.at(type)) {
    }

    ~FunctionBinaryOperator() = default;

    const std::string& getName() const {
        return name_;
    }

    mukyu::cablin::core::Value execute(mukyu::cablin::core::Controller*,
                                       mukyu::cablin::core::ValueList params) {
        if (params.size() != 2) {
            throw std::runtime_error("FunctionBinaryOperator<" + name_ +
                                     ">::execute: |params| should be 2");
        }

        return func_(params[0], params[1]);
    }

private:
    std::string name_;
    BinaryOperatorFunctionType func_;
};

using FunctionOperatorPlus = FunctionBinaryOperator<BinaryOperatorType::PLUS>;
using FunctionOperatorMinus = FunctionBinaryOperator<BinaryOperatorType::MINUS>;
using FunctionOperatorMultiply =
    FunctionBinaryOperator<BinaryOperatorType::MULTIPLY>;
using FunctionOperatorDivide =
    FunctionBinaryOperator<BinaryOperatorType::DIVIDE>;
using FunctionOperatorMod = FunctionBinaryOperator<BinaryOperatorType::MOD>;

using FunctionOperatorAnd = FunctionBinaryOperator<BinaryOperatorType::AND>;
using FunctionOperatorOr = FunctionBinaryOperator<BinaryOperatorType::OR>;

using FunctionOperatorEqual = FunctionBinaryOperator<BinaryOperatorType::EQUAL>;
using FunctionOperatorLess = FunctionBinaryOperator<BinaryOperatorType::LESS>;
using FunctionOperatorGreater =
    FunctionBinaryOperator<BinaryOperatorType::GREATER>;
using FunctionOperatorLessEqual =
    FunctionBinaryOperator<BinaryOperatorType::LESS_EQUAL>;
using FunctionOperatorGreaterEqual =
    FunctionBinaryOperator<BinaryOperatorType::GREATER_EQUAL>;


}  // namespace function
}  // namespace cablin
}  // namespace mukyu