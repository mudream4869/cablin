#include <mukyu/cablin/expr/unary_op.hpp>

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/expr.hpp>
#include <mukyu/cablin/expr/factory.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


namespace mccore = mukyu::cablin::core;


class ExprUnaryOperator::Impl {
public:
    Impl(const std::string& name, const mccore::ConfigPtr& node)
        : expr_(createExpr(node)),
          func_(FUNCTION_UNARY_OPERATOR_FUNC_MAP.at(name)) {
    }

    ~Impl() = default;

    mccore::Value compute(mccore::Controller* controller) {
        return func_(expr_->compute(controller));
    }

private:
    UnaryOperatorFunctionType func_;
    mccore::ExprPtr expr_;
};

ExprUnaryOperator::ExprUnaryOperator(const std::string& name,
                                     const mccore::ConfigPtr& node)
    : impl_(std::make_unique<Impl>(name, node)) {
}

ExprUnaryOperator::~ExprUnaryOperator() = default;

mccore::Value ExprUnaryOperator::compute(mccore::Controller* controller) {
    return impl_->compute(controller);
}


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu