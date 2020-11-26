#pragma once

#include <mukyu/cablin/core/expr.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace expr {


mukyu::cablin::core::ExprPtr createExpr(const YAML::Node& node);


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu