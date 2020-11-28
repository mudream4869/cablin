#include <gtest/gtest.h>

#include <mukyu/cablin/command/var.hpp>
#include <mukyu/cablin/core/controller.hpp>

namespace mccmd = mukyu::cablin::command;
namespace mccore = mukyu::cablin::core;

TEST(COMMAND_VAR, COMMAND_VAR_TESTINT_1) {
    auto node = YAML::Load(
        "type: int\n"
        "name: a\n"
        "default_value: 123\n");

    auto commandVar = mccmd::CommandVar(node);

    mccore::Controller controller;
    commandVar.execute(&controller);

    auto ans = mccore::Value(123);
    auto res = controller.getLocalVar("a");

    ASSERT_TRUE((res == ans).as<bool>());
}

TEST(COMMAND_VAR, COMMAND_VAR_TESTINT_2) {
    auto node = YAML::Load(
        "type: bool\n"
        "name: a\n"
        "default_value: false\n");

    auto commandVar = mccmd::CommandVar(node);

    mccore::Controller controller;
    commandVar.execute(&controller);

    auto ans = mccore::Value(false);
    auto res = controller.getLocalVar("a");

    ASSERT_TRUE((res == ans).as<bool>());
}
