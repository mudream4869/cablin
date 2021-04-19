#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/expr.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


mukyu::cablin::core::ExprPtr createExpr(
    const mukyu::cablin::core::ConfigPtr& node);

// createSimpleExpr only allow operator/const/var expression
mukyu::cablin::core::ExprPtr createSimpleExpr(
    const mukyu::cablin::core::ConfigPtr& node);


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu