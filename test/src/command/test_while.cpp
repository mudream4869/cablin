#include <gtest/gtest.h>

#include <mukyu/cablin/command/while.hpp>
#include <mukyu/cablin/core/controller.hpp>

namespace mccmd = mukyu::cablin::command;
namespace mccore = mukyu::cablin::core;

TEST(COMMAND_WHILE, COMMAND_WHILE_WORK) {
    std::string body = R"(
condition:
  get: run
body:
  - assign:
      target: run
      source:
        const:
          type: bool
          value: false
)";
    auto node = YAML::Load(body);

    std::string package = "main";

    auto commandIf = mccmd::CommandWhile(package, node);

    mccore::Controller controller;
    controller.addLocalVar("run", true);
    commandIf.execute(&controller);

    ASSERT_TRUE((controller.getLocalVar("run") == false).as<bool>());
}

TEST(COMMAND_WHILE, COMMAND_WHILE_BREAK) {
    std::string body = R"(
condition:
  get: run
body:
  - break:
  - assign:
      target: run
      source:
        const:
          type: bool
          value: false
)";
    auto node = YAML::Load(body);

    std::string package = "main";

    auto commandIf = mccmd::CommandWhile(package, node);

    mccore::Controller controller;
    controller.addLocalVar("run", true);
    commandIf.execute(&controller);

    ASSERT_TRUE((controller.getLocalVar("run") == true).as<bool>());
}
