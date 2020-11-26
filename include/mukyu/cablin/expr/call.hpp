#pragma once

#include <mukyu/cablin/core/expr.hpp>

#include <mukyu/cablin/command/call.hpp>

#include <yaml-cpp/yaml.h>

#include <memory>


namespace mukyu {
namespace cablin {
namespace expr {


const std::string EXPRCALL_NAME = "call";

class ExprCall : public mukyu::cablin::core::Expr {
public:
    ExprCall(const YAML::Node& node);
    ~ExprCall();

    mukyu::cablin::core::Value compute(
        mukyu::cablin::core::Controller* controller);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu