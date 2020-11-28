#include <gtest/gtest.h>

#include <mukyu/cablin/function/functor.hpp>
#include <mukyu/cablin/core/controller.hpp>

namespace mcfunc = mukyu::cablin::function;
namespace mccore = mukyu::cablin::core;

TEST(FUNCTION_FUNCTOR, FUNCTION_FUNCTOR_WORK) {
    std::string package = "main";
    bool flag = false;
    auto func = [&flag](mccore::ValueList) {
        flag = true;
        return mccore::Value(1);
    };

    auto funcNode = mcfunc::FunctionFunctor("functor", func);

    mccore::Controller controller;
    controller.addPackage(package);
    controller.addPackageVar(package, "run", false);

    funcNode.execute(&controller, {});

    ASSERT_TRUE(flag);
}
