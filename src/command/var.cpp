#include <mukyu/cablin/command/var.hpp>

#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <stdexcept>
#include <string>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;


class CommandVar::Impl {
public:
    Impl(const YAML::Node& node) : name_(node["name"].as<std::string>()) {
        const auto& valueNode = node["default_value"];
        type_ = mccore::STR_VALUETYPE_MAP.at(node["type"].as<std::string>());
        defaultValue_ = mccommon::valueNodeToValue(type_, valueNode);
    }

    ~Impl() = default;

    mccore::Value execute(mccore::Controller* controller) {
        controller->addLocalVar(name_, defaultValue_);
        return defaultValue_;
    }

private:
    std::string name_;
    mccore::ValueType type_;
    mccore::Value defaultValue_;
};

CommandVar::CommandVar(const YAML::Node& node)
    : impl_(std::make_unique<Impl>(node)) {
}

CommandVar::~CommandVar() = default;

mccore::Value CommandVar::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu