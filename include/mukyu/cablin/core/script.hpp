#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/value.hpp>
#include <mukyu/cablin/core/package.hpp>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>


namespace mukyu {
namespace cablin {
namespace core {


class Script final {
public:
    explicit Script(const std::string& importDir);

    ~Script();

    void addFile(const std::string& name, const std::string& filename);

    void addFile(const std::string& filename);

    void addYamlNode(const std::string& name,
                     const mukyu::cablin::core::ConfigPtr& root);

    void addPackage(PackagePtr package);

    Value callFunction(const std::string& packageName,
                       const std::string& functionName,
                       std::vector<Value> params);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu