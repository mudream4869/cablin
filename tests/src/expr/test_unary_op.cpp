#include <mukyu/cablin/expr/unary_op.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/config/yamlconfig.hpp>

#include <gtest/gtest.h>

namespace mcexpr = mukyu::cablin::expr;
namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;

TEST(EXPR_UNARY_OP, EXPR_UNARY_OP_NOT) {
    std::string body = R"(
const:
  type: bool
  value: false
)";
    auto node = mcconf::createYAMLConfigFromString(body);

    auto exprNot = mcexpr::ExprUnaryOperator("not", node);

    mccore::Controller controller;

    auto value = exprNot.compute(&controller);

    ASSERT_TRUE((value == mccore::Value(true)).as<bool>());
}

TEST(EXPR_UNARY_OP, EXPR_UNARY_OP_NEG) {
    std::string body = R"(
const:
  type: int
  value: 1
)";
    auto node = mcconf::createYAMLConfigFromString(body);

    auto exprNeg = mcexpr::ExprUnaryOperator("neg", node);

    mccore::Controller controller;

    auto value = exprNeg.compute(&controller);

    ASSERT_TRUE((value == mccore::Value(-1)).as<bool>());
}
