#include <mukyu/cablin/command/assign.hpp>

#include <mukyu/cablin/command/factory.hpp>

#include <mukyu/cablin/expr/factory.hpp>

#include <mukyu/cablin/common/string.hpp>

#include <string>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


class CommandAssign::Impl {
public:
    Impl(const mccore::ConfigPtr& node)
        : source_(mcexpr::createExpr(node->at("source"))) {
        // parsing <package>::<name>
        auto target = node->at("target")->as<std::string>();
        std::tie(varPackage_, target_) = mccommon::splitPackage(target);
    }

    mccore::Value execute(mccore::Controller* controller) {
        mccore::Value value = source_->compute(controller);
        if (!varPackage_.empty()) {
            controller->setPackageVar(varPackage_, target_, value);
            return value;
        }

        try {
            controller->setLocalVar(target_, value);
        } catch (const std::out_of_range&) {
            auto curPackage = controller->getCurrentPackageName();
            controller->setPackageVar(curPackage, target_, value);
        }

        return value;
    }

private:
    std::string varPackage_;
    std::string target_;
    mccore::ExprPtr source_;
};

CommandAssign::CommandAssign(const mccore::ConfigPtr& node)
    : impl_(std::make_unique<Impl>(node)) {
}

CommandAssign::~CommandAssign() = default;

mccore::Value CommandAssign::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu