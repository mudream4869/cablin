#include <mukyu/cablin/expr/call.hpp>

#include <mukyu/cablin/command/call.hpp>


namespace mukyu {
namespace cablin {
namespace expr {


namespace mccmd = mukyu::cablin::command;
namespace mccore = mukyu::cablin::core;


class ExprCall::Impl {
public:
    Impl(const YAML::Node& node)
        : callCmd_(std::make_unique<mccmd::CommandCall>(node)) {
    }

    ~Impl() = default;

    mccore::Value compute(mccore::Controller* controller) {
        return callCmd_->execute(controller);
    }

private:
    mccore::CommandPtr callCmd_;
};

ExprCall::ExprCall(const YAML::Node& node)
    : impl_(std::make_unique<Impl>(node)) {
}

ExprCall::~ExprCall() = default;

mccore::Value ExprCall::compute(mccore::Controller* controller) {
    return impl_->compute(controller);
}


}  // namespace expr
}  // namespace cablin
}  // namespace mukyu