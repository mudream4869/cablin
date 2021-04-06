#include <mukyu/cablin/config/yamlconfig.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace config {


namespace mccore = mukyu::cablin::core;


class YamlConfig::Impl {
public:
    Impl() = default;
    ~Impl() = default;

    explicit Impl(const YAML::Node& node) : node(node) {
    }

    YAML::Node node;
};

YamlConfig::YamlConfig() : impl_(std::make_unique<Impl>()) {
}

YamlConfig::~YamlConfig() {
}

void YamlConfig::loadFromFile(const std::string& filename) {
    impl_->node = YAML::LoadFile(filename);
}

void YamlConfig::loadFromString(const std::string& cont) {
    impl_->node = YAML::Load(cont);
}

mccore::ConfigPtr YamlConfig::at(const std::string& key) const {
    if (!impl_->node.IsMap()) {
        throw mccore::ConfigTypeError("map");
    }

    auto retNode = impl_->node[key];
    if (retNode) {
        auto retImpl = std::make_unique<Impl>(retNode);
        return createByImpl(std::move(retImpl));
    }

    return nullptr;
}

mccore::ConfigPtr YamlConfig::at(size_t index) const {
    if (!impl_->node.IsSequence()) {
        throw mccore::ConfigTypeError("list");
    }

    return createByImpl(std::make_unique<Impl>(impl_->node[index]));
}

size_t YamlConfig::size() const {
    if (!impl_->node.IsSequence() && !impl_->node.IsMap()) {
        throw mccore::ConfigTypeError("list or map");
    }

    return impl_->node.size();
}

std::vector<std::string> YamlConfig::keys() const {
    if (!impl_->node.IsMap()) {
        throw mccore::ConfigTypeError("map");
    }

    std::vector<std::string> ret;
    for (const auto& it : impl_->node) {
        ret.emplace_back(it.first.as<std::string>());
    }
    return ret;
}

bool YamlConfig::isList() const {
    return impl_->node.IsSequence();
}

bool YamlConfig::isMap() const {
    return impl_->node.IsMap();
}

bool YamlConfig::isScalar() const {
    return impl_->node.IsScalar();
}

bool YamlConfig::isNull() const {
    return impl_->node.IsNull();
}

std::optional<mccore::ConfigMark> YamlConfig::getMark() const {
    auto nmark = impl_->node.Mark();
    mccore::ConfigMark retMark;
    retMark.line = nmark.line;
    retMark.col = nmark.column;
    retMark.pos = nmark.pos;
    return retMark;
}

int YamlConfig::asInt() const {
    if (!impl_->node.IsScalar()) {
        throw mccore::ConfigTypeError("scalar");
    }

    return impl_->node.as<int>();
}

int64_t YamlConfig::asInt64() const {
    if (!impl_->node.IsScalar()) {
        throw mccore::ConfigTypeError("scalar");
    }

    return impl_->node.as<int64_t>();
}

std::string YamlConfig::asString() const {
    if (!impl_->node.IsScalar()) {
        throw mccore::ConfigTypeError("scalar");
    }

    return impl_->node.as<std::string>();
}

float YamlConfig::asFloat() const {
    if (!impl_->node.IsScalar()) {
        throw mccore::ConfigTypeError("scalar");
    }

    return impl_->node.as<float>();
}

bool YamlConfig::asBool() const {
    if (!impl_->node.IsScalar()) {
        throw mccore::ConfigTypeError("scalar");
    }

    return impl_->node.as<bool>();
}

std::unique_ptr<YamlConfig> YamlConfig::createByImpl(
    std::unique_ptr<Impl>&& impl) {
    auto ret = std::make_unique<YamlConfig>();
    ret->impl_ = std::move(impl);
    return ret;
}


}  // namespace config
}  // namespace cablin
}  // namespace mukyu
