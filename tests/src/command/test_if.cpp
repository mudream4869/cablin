#include <mukyu/cablin/config/yamlconfig.hpp>

#include <mukyu/cablin/command/if.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <gtest/gtest.h>

namespace mccmd = mukyu::cablin::command;
namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;

TEST(COMMAND_IF, COMMAND_IF_WORK_THEN) {
    std::string body = R"(
condition:
  const:
    type: bool
    value: true
then:
  - assign:
      target: work
      source:
        const:
          type: bool
          value: true
)";
    auto conf = mcconf::createYAMLConfigFromString(body);
    std::string package = "main";

    auto commandIf = mccmd::CommandIf(conf);

    mccore::Controller controller;
    controller.addLocalVar("work", false);
    commandIf.execute(&controller);

    ASSERT_TRUE(
        (controller.getLocalVar("work") == mccore::Value(true)).as<bool>());
}

TEST(COMMAND_IF, COMMAND_IF_WORK_ELSE) {
    std::string body = R"(
condition:
  const:
    type: bool
    value: false
else:
  - assign:
      target: work
      source:
        const:
          type: bool
          value: true
)";
    auto conf = mcconf::createYAMLConfigFromString(body);

    std::string package = "main";

    auto commandIf = mccmd::CommandIf(conf);

    mccore::Controller controller;
    controller.addLocalVar("work", false);
    commandIf.execute(&controller);

    ASSERT_TRUE(
        (controller.getLocalVar("work") == mccore::Value(true)).as<bool>());
}
