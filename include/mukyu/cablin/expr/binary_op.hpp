#pragma once

#include <mukyu/cablin/common/yamlutil.hpp>
#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/expr.hpp>

#include <functional>
#include <unordered_map>


namespace mukyu {
namespace cablin {
namespace expr {


using BinaryOperatorFunctionType = std::function<mukyu::cablin::core::Value(
    const mukyu::cablin::core::Value&, const mukyu::cablin::core::Value&)>;

const std::unordered_map<std::string, BinaryOperatorFunctionType>
    FUNCTION_BINARY_OPERATOR_FUNC_MAP = {
        {"plus", [](const auto& v1, const auto& v2) { return v1 + v2; }},
        {"minus", [](const auto& v1, const auto& v2) { return v1 - v2; }},
        {"multiply", [](const auto& v1, const auto& v2) { return v1 * v2; }},
        {"divide", [](const auto& v1, const auto& v2) { return v1 / v2; }},
        {"mod", [](const auto& v1, const auto& v2) { return v1 % v2; }},
        {"and", [](const auto& v1, const auto& v2) { return v1 && v2; }},
        {"or", [](const auto& v1, const auto& v2) { return v1 || v2; }},
        {"equal", [](const auto& v1, const auto& v2) { return v1 == v2; }},
        {"not_equal", [](const auto& v1, const auto& v2) { return v1 != v2; }},
        {"less", [](const auto& v1, const auto& v2) { return v1 < v2; }},
        {"greater", [](const auto& v1, const auto& v2) { return v1 > v2; }},
        {"less_equal", [](const auto& v1, const auto& v2) { return v1 <= v2; }},
        {"greater_equal",
         [](const auto& v1, const auto& v2) { return v1 >= v2; }},
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