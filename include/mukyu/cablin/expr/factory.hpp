#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/expr.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


mukyu::cablin::core::ExprPtr createExpr(
    const mukyu::cablin::core::ConfigPtr& node);


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu