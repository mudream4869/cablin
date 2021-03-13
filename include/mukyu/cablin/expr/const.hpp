#pragma once

#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/expr.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


const std::string EXPRCONST_NAME = "const";

class ExprConst : public mukyu::cablin::core::Expr {
public:
    // value = None
    ExprConst() = default;

    ExprConst(const mukyu::cablin::core::ConfigPtr& node) {
        auto type = mukyu::cablin::core::STR_VALUETYPE_MAP.at(
            node->at("type")->as<std::string>());

        v = mukyu::cablin::common::valueNodeToValue(type, node->at("value"));
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