#include <mukyu/cablin/expr/binary_op.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/config/yamlconfig.hpp>

#include <gtest/gtest.h>

namespace mcexpr = mukyu::cablin::expr;
namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;

TEST(EXPR_BINARY_OP, EXPR_BINARY_OP_AND) {
    std::string body = R"(
- const:
    type: bool
    value: false
- const:
    type: bool
    value: true
)";
    auto node = mcconf::createYAMLConfigFromString(body);

    auto exprAnd = mcexpr::ExprBinaryOperator("and", node);

    mccore::Controller controller;

    auto value = exprAnd.compute(&controller);

    ASSERT_TRUE((value == mccore::Value(false)).as<bool>());
}

TEST(EXPR_BINARY_OP, EXPR_BINARY_OP_OR) {
    std::string body = R"(
- const:
    type: bool
    value: false
- const:
    type: bool
    value: true
)";
    auto node = mcconf::createYAMLConfigFromString(body);

    auto exprOr = mcexpr::ExprBinaryOperator("or", node);

    mccore::Controller controller;

    auto value = exprOr.compute(&controller);

    ASSERT_TRUE((value == mccore::Value(true)).as<bool>());
}
