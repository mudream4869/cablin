#pragma once

#include <mukyu/cablin/command/flow.hpp>

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/expr/factory.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace command {


const std::string COMMANDRETURN_KEY = "return";

class CommandReturn : public mukyu::cablin::core::Command {
public:
    CommandReturn(const YAML::Node& node)
        : expr_(mukyu::cablin::expr::createExpr(node)) {
    }

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller) {
        throw ReturnException(expr_->compute(controller));
    }

private:
    mukyu::cablin::core::ExprPtr expr_;
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu