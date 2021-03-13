#include <mukyu/cablin/command/block.hpp>
#include <mukyu/cablin/command/var.hpp>

#include <mukyu/cablin/config/yamlconfig.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <gtest/gtest.h>

namespace mccmd = mukyu::cablin::command;
namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;

TEST(COMMAND_BLOCK, COMMAND_BLOCK) {
    std::string body = R"(
- var:
    name: var1
    type: int
    default_value: 1
- block:
    - var:
        name: var1
        type: int
        default_value: 2
    - assign:
        target: a
        source:
          get: var1
)";
    auto conf = mcconf::createYAMLConfigFromString(body);

    std::string package = "main";

    auto commandBlock = mccmd::CommandBlock(conf);
    return;

    mccore::Controller controller;
    controller.addPackage(package);
    controller.addPackageVar(package, "a", 0);

    commandBlock.execute(&controller);

    auto ans = mccore::Value(2);
    auto res = controller.getPackageVar(package, "a");

    ASSERT_TRUE((res == ans).as<bool>());
}
