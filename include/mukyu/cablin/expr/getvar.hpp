#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/expr.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


const std::string EXPRGET_NAME = "get";

class ExprGet : public mukyu::cablin::core::Expr {
public:
    ExprGet(const mukyu::cablin::core::ConfigPtr& node);

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