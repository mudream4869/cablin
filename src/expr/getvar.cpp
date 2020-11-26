#include <mukyu/cablin/expr/getvar.hpp>

#include <mukyu/cablin/core/expr.hpp>
#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/common/string.hpp>

#include <yaml-cpp/yaml.h>

#include <iostream>


namespace mukyu {
namespace cablin {
namespace expr {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;


ExprGet::ExprGet(const YAML::Node& node) {
    auto varName = node.as<std::string>();
    std::tie(packageName_, varName_) = mccommon::splitPackage(varName);
}

ExprGet::~ExprGet() = default;

mccore::Value ExprGet::compute(mccore::Controller* controller) {
    if (!packageName_.empty()) {
        return controller->getPackageVar(packageName_, varName_);
    }

    try {
        return controller->getLocalVar(varName_);
    } catch (const std::out_of_range& ex) {
        auto curPackage = controller->getCurrentPackageName();
        return controller->getPackageVar(curPackage, varName_);
    }
}


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu