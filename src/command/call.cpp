#include <mukyu/cablin/command/call.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/common/string.hpp>

#include <mukyu/cablin/expr/factory.hpp>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


class CommandCall::Impl {
public:
    Impl(const YAML::Node& node) {
        const auto& paramsNode = node["params"];
        if (paramsNode != nullptr) {
            for (const auto& item : paramsNode) {
                params_.push_back(mcexpr::createExpr(item));
            }
        }

        // parsing <package>::<name>
        auto name = node["name"].as<std::string>();
        std::tie(varPackage_, name_) = mccommon::splitPackage(name);
    }

    ~Impl() = default;

    mccore::Value execute(mccore::Controller* controller) {
        std::vector<mccore::Value> params(params_.size());
        for (size_t i = 0; i < params_.size(); ++i) {
            params[i] = params_[i]->compute(controller);
        }

        if (!varPackage_.empty()) {
            return controller->callFunction(varPackage_, name_, params);
        } else {
            auto curPackage = controller->getCurrentPackageName();
            return controller->callFunction(curPackage, name_, params);
        }
    }

private:
    std::string varPackage_;
    std::string name_;
    std::vector<mccore::ExprPtr> params_;
};

CommandCall::CommandCall(const YAML::Node& node)
    : impl_(std::make_unique<Impl>(node)) {
}

CommandCall::~CommandCall() = default;

mccore::Value CommandCall::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu