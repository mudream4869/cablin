#include <gtest/gtest.h>

#include <mukyu/cablin/expr/const.hpp>
#include <mukyu/cablin/core/controller.hpp>

namespace mcexpr = mukyu::cablin::expr;
namespace mccore = mukyu::cablin::core;

TEST(EXPR_CONST, EXPR_CONST_BOOL) {
    auto node = YAML::Load(
        "type: bool\n"
        "value: false\n");

    auto exprConst = mcexpr::ExprConst(node);

    mccore::Controller controller;

    auto value = exprConst.compute(&controller);

    ASSERT_TRUE((value == mccore::Value(false)).as<bool>());
}

TEST(EXPR_CONST, EXPR_CONST_NONE) {
    auto exprConst = mcexpr::ExprConst();

    mccore::Controller controller;

    auto value = exprConst.compute(&controller);

    ASSERT_EQ(value.type(), mccore::ValueType::NONE);
}
