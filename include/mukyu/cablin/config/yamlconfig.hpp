#pragma once

#include <mukyu/cablin/core/config.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace config {


class YamlConfig : public mukyu::cablin::core::Config {
public:
    YamlConfig();
    ~YamlConfig();

    void loadFromFile(const std::string& filename);
    void loadFromString(const std::string& cont);

    mukyu::cablin::core::ConfigPtr at(const std::string& key) const;

    mukyu::cablin::core::ConfigPtr at(size_t index) const;

    size_t size() const;

    std::vector<std::string> keys() const;

    bool isList() const;
    bool isMap() const;
    bool isScalar() const;
    bool isNull() const;

    virtual std::string path() const;

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


inline mukyu::cablin::core::ConfigPtr createYAMLConfigFromFile(
    const std::string& filename) {
    auto conf = std::make_unique<YamlConfig>();
    conf->loadFromFile(filename);
    return conf;
}

inline mukyu::cablin::core::ConfigPtr createYAMLConfigFromString(
    const std::string& cont) {
    auto conf = std::make_unique<YamlConfig>();
    conf->loadFromString(cont);
    return conf;
}


}  // namespace config
}  // namespace cablin
}  // namespace mukyu
