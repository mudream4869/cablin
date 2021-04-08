#pragma once

#include <functional>
#include <mukyu/cablin/common/yamlutil.hpp>
#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/expr.hpp>
#include <unordered_map>


namespace mukyu {
namespace cablin {
namespace expr {


using BinaryOperatorFunctionType = std::function<mukyu::cablin::core::Value(
    const mukyu::cablin::core::Value&, const mukyu::cablin::core::Value&)>;

const std::unordered_map<std::string, BinaryOperatorFunctionType>
    FUNCTION_BINARY_OPERATOR_FUNC_MAP = {
        {"plus", mukyu::cablin::core::operator+ },
        {"minus", mukyu::cablin::core::operator- },
        {"multiply", mukyu::cablin::core::operator* },
        {"divide", mukyu::cablin::core::operator/ },
        {"mod", mukyu::cablin::core::operator% },
        {"and", mukyu::cablin::core::operator&& },
        {"or", mukyu::cablin::core::operator|| },
        {"equal", mukyu::cablin::core::operator== },
        {"less", mukyu::cablin::core::operator<},
        {"greater", mukyu::cablin::core::operator> },
        {"less_equal", mukyu::cablin::core::operator<= },
        {"greater_equal", mukyu::cablin::core::operator>=},
    };


class ExprBinaryOperator : public mukyu::cablin::core::Expr {
public:
    ExprBinaryOperator(const std::string& name,
                      const mukyu::cablin::core::ConfigPtr& node);

    ~ExprBinaryOperator();

    mukyu::cablin::core::Value compute(mukyu::cablin::core::Controller*);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu