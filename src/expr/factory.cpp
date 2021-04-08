#include <mukyu/cablin/common/yamlutil.hpp>
#include <mukyu/cablin/core/error.hpp>
#include <mukyu/cablin/expr/call.hpp>
#include <mukyu/cablin/expr/const.hpp>
#include <mukyu/cablin/expr/factory.hpp>
#include <mukyu/cablin/expr/getvar.hpp>
#include <mukyu/cablin/expr/unary_op.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


mccore::ExprPtr createExpr(const mccore::ConfigPtr& node) {
    auto key = mccommon::getSingleKey(node);
    if (!key.has_value()) {
        if (node->isMap() && node->size() == 0) {
            return std::make_unique<mcexpr::ExprConst>();
        }

        throw mccore::CablinParsingException(
            "createExpr: should be single-key-map", node->path());
    }

    auto obj = node->at(key.value());

    if (key == mcexpr::EXPRCONST_NAME) {
        return std::make_unique<mcexpr::ExprConst>(obj);
    } else if (key == mcexpr::EXPRGET_NAME) {
        return std::make_unique<mcexpr::ExprGet>(obj);
    } else if (key == mcexpr::EXPRCALL_NAME) {
        return std::make_unique<mcexpr::ExprCall>(obj);
    }

    if (FUNCTION_UNARY_OPERATOR_FUNC_MAP.find(key.value()) !=
        FUNCTION_UNARY_OPERATOR_FUNC_MAP.end()) {
        return std::make_unique<mcexpr::ExprUnaryOperator>(key.value(), obj);
    }

    throw mccore::CablinParsingException(
        "createExpr: " + key.value() + " is not an expr type", node->path());
}


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu