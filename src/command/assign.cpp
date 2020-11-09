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
    Impl(const std::string& package, const YAML::Node& node)
        : source_(mcexpr::createExpr(package, node["source"])),
          package_(package) {
        // parsing <package>::<name>
        auto target = node["target"].as<std::string>();
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
            controller->setPackageVar(std::string(package_), target_, value);
        }

        return value;
    }

private:
    const std::string& package_;
    std::string varPackage_;
    std::string target_;
    mccore::ExprPtr source_;
};

CommandAssign::CommandAssign(const std::string& package, const YAML::Node& node)
    : impl_(std::make_unique<Impl>(package, node)) {
}

CommandAssign::~CommandAssign() = default;

mccore::Value CommandAssign::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu