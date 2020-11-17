#include <mukyu/cablin/command/globalvar.hpp>

#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <stdexcept>
#include <string>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;


class CommandGlobalVar::Impl {
public:
    Impl(const std::string& package, const YAML::Node& node)
        : name_(node["name"].as<std::string>()), package_(package) {
        const auto& valueNode = node["default_value"];
        type_ = mccore::STR_VALUETYPE_MAP.at(node["type"].as<std::string>());
        defaultValue_ = mccommon::valueNodeToValue(type_, valueNode);
    }

    ~Impl() = default;

    mccore::Value execute(mccore::Controller* controller) {
        controller->addPackageVar(package_, name_, defaultValue_);
        return defaultValue_;
    }

private:
    const std::string& package_;
    std::string name_;
    mccore::ValueType type_;
    mccore::Value defaultValue_;
};

CommandGlobalVar::CommandGlobalVar(const std::string& package,
                                   const YAML::Node& node)
    : impl_(std::make_unique<Impl>(package, node)) {
}

CommandGlobalVar::~CommandGlobalVar() = default;

mccore::Value CommandGlobalVar::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu