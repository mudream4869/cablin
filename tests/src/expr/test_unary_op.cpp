#include <mukyu/cablin/expr/unary_op.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/config/yamlconfig.hpp>

#include <gtest/gtest.h>

namespace mcexpr = mukyu::cablin::expr;
namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;

TEST(EXPR_CONST, EXPR_NOT) {
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
