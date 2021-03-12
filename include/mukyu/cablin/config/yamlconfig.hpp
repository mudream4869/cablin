#pragma once

#include <mukyu/cablin/core/config.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace config {


class YamlConfig : public mukyu::cablin::core::Config {
public:
    YamlConfig();
    ~YamlConfig() = default;

    void loadFromFile(const std::string& filename);
    void loadFromString(const std::string& cont);

    std::unique_ptr<mukyu::cablin::core::Config> at(
        const std::string& key) const;

    std::unique_ptr<mukyu::cablin::core::Config> at(size_t index) const;

    size_t size() const;

    std::vector<std::string> keys() const;

    bool isList() const;
    bool isMap() const;
    bool isScalar() const;
    bool isNull() const;

    std::optional<mukyu::cablin::core::ConfigMark> getMark() const;

protected:
    int asInt() const;
    int64_t asInt64() const;
    std::string asString() const;
    float asFloat() const;
    bool asBool() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

    static std::unique_ptr<YamlConfig> createByImpl(
        std::unique_ptr<Impl>&& impl);

    static std::unique_ptr<YamlConfig> createByImpl(
        const std::unique_ptr<Impl>& impl) = delete;
};


}  // namespace config
}  // namespace cablin
}  // namespace mukyu
