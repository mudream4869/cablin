#pragma once

#include <mukyu/cablin/core/expr.hpp>
#include <mukyu/cablin/core/controller.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace expr {


const std::string EXPRGET_NAME = "get";

class ExprGet : public mukyu::cablin::core::Expr {
public:
    ExprGet(const YAML::Node& node);

    ~ExprGet();

    mukyu::cablin::core::Value compute(
        mukyu::cablin::core::Controller* controller);

private:
    std::string packageName_;
    std::string varName_;
};


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu