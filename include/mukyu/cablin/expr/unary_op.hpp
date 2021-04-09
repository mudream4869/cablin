#pragma once

#include <mukyu/cablin/common/yamlutil.hpp>
#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/expr.hpp>

#include <functional>
#include <unordered_map>


namespace mukyu {
namespace cablin {
namespace expr {


using UnaryOperatorFunctionType = std::function<mukyu::cablin::core::Value(
    const mukyu::cablin::core::Value&)>;

const std::unordered_map<std::string, UnaryOperatorFunctionType>
    FUNCTION_UNARY_OPERATOR_FUNC_MAP = {
        {"not", [](const auto& v) { return !v; }},
        {"neg", [](const auto& v) { return -v; }},
};


class ExprUnaryOperator : public mukyu::cablin::core::Expr {
public:
    ExprUnaryOperator(const std::string& name,
                      const mukyu::cablin::core::ConfigPtr& node);

    ~ExprUnaryOperator();

    mukyu::cablin::core::Value compute(mukyu::cablin::core::Controller*);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu