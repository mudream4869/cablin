#include <mukyu/cablin/expr/binary_op.hpp>

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/expr.hpp>
#include <mukyu/cablin/expr/factory.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


namespace mccore = mukyu::cablin::core;


class ExprBinaryOperator::Impl {
public:
    Impl(const std::string& name, const mccore::ConfigPtr& node):
        func_(FUNCTION_BINARY_OPERATOR_FUNC_MAP.at(name)),
        expr1_(createExpr(node->at(0))),
        expr2_(createExpr(node->at(1))) {
    
    }

    ~Impl() = default;

    mccore::Value compute(mccore::Controller* controller) {
        return func_(expr1_->compute(controller), expr2_->compute(controller));
    }

private:
    BinaryOperatorFunctionType func_;
    mccore::ExprPtr expr1_;
    mccore::ExprPtr expr2_;
};

ExprBinaryOperator::ExprBinaryOperator(const std::string& name,
                                     const mccore::ConfigPtr& node)
    : impl_(std::make_unique<Impl>(name, node)) {
}

ExprBinaryOperator::~ExprBinaryOperator() = default;

mccore::Value ExprBinaryOperator::compute(mccore::Controller* controller) {
    return impl_->compute(controller);
}


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu