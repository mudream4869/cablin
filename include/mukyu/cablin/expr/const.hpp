#pragma once

#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/core/expr.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace expr {


const std::string EXPRCONST_NAME = "const";

class ExprConst : public mukyu::cablin::core::Expr {
public:
    // value = None
    ExprConst() = default;

    ExprConst(const YAML::Node& node) {
        auto type = mukyu::cablin::core::STR_VALUETYPE_MAP.at(
            node["type"].as<std::string>());

        v = mukyu::cablin::common::valueNodeToValue(type, node["value"]);
    }

    ~ExprConst() = default;

    mukyu::cablin::core::Value compute(mukyu::cablin::core::Controller*) {
        return v;
    }

private:
    mukyu::cablin::core::Value v;
};


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu