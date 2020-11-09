#include <mukyu/cablin/expr/factory.hpp>

#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/expr/const.hpp>
#include <mukyu/cablin/expr/getvar.hpp>
#include <mukyu/cablin/expr/call.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


mccore::ExprPtr createExpr(const std::string& package, const YAML::Node& node) {
    auto key = mccommon::getSingleKey(node);
    if (!key.has_value()) {
        if (node.IsMap() && node.size() == 0) {
            return std::make_unique<mcexpr::ExprConst>();
        }
        throw std::runtime_error("createExpr: should be single-key-map");
    }

    const auto& obj = node[key.value()];

    if (key == mcexpr::EXPRCONST_NAME) {
        return std::make_unique<mcexpr::ExprConst>(obj);
    } else if (key == mcexpr::EXPRGET_NAME) {
        return std::make_unique<mcexpr::ExprGet>(package, obj);
    } else if (key == mcexpr::EXPRCALL_NAME) {
        return std::make_unique<mcexpr::ExprCall>(package, obj);
    }

    throw std::runtime_error("createExpr: " + key.value() +
                             " is not an expr type");
}


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu