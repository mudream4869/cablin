#include <gtest/gtest.h>

#include <mukyu/cablin/function/node.hpp>
#include <mukyu/cablin/core/controller.hpp>

namespace mcfunc = mukyu::cablin::function;
namespace mccore = mukyu::cablin::core;

TEST(FUNCTION_NODE, FUNCTION_NODE_WORK) {
    std::string body = R"(
name: myFunc
params: []
body:
  - assign:
      target: run
      source:
        const:
          type: bool
          value: true
)";
    auto node = YAML::Load(body);

    std::string package = "main";

    auto funcNode = mcfunc::FunctionNode(package, node);

    mccore::Controller controller;
    controller.addPackage(package);
    controller.addPackageVar(package, "run", false);

    funcNode.execute(&controller, {});

    auto result = controller.getPackageVar(package, "run") == true;
    ASSERT_TRUE(result.as<bool>());
}

TEST(FUNCTION_NODE, FUNCTION_NODE_PARAM) {
    std::string body = R"(
name: myFunc
params:
  - type: bool
    name: ok
body:
  - assign:
      target: run
      source:
        get: ok
)";
    auto node = YAML::Load(body);

    std::string package = "main";

    auto funcNode = mcfunc::FunctionNode(package, node);

    mccore::Controller controller;
    controller.addPackage(package);
    controller.addPackageVar(package, "run", false);

    funcNode.execute(&controller, {true});

    auto result = controller.getPackageVar(package, "run") == true;
    ASSERT_TRUE(result.as<bool>());
}

TEST(FUNCTION_NODE, FUNCTION_NODE_RETURN) {
    std::string body = R"(
name: myFunc
params: []
body:
  - return:
      const:
        type: int
        value: 123
)";
    auto node = YAML::Load(body);

    std::string package = "main";

    auto funcNode = mcfunc::FunctionNode(package, node);

    mccore::Controller controller;
    controller.addPackage(package);
    controller.addPackageVar(package, "run", false);

    auto returnValue = funcNode.execute(&controller, {});

    auto result = returnValue == 123;
    ASSERT_TRUE(result.as<bool>());
}
