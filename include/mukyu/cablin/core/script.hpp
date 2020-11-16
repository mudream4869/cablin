#pragma once

#include <mukyu/cablin/core/value.hpp>
#include <mukyu/cablin/core/package.hpp>

#include <yaml-cpp/yaml.h>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>


namespace mukyu {
namespace cablin {
namespace core {


class Script final {
public:
    using PackagePtrMap = std::unordered_map<std::string, PackagePtr>;

    Script(const std::string& filename);
    Script(const std::string& filename, PackagePtrMap packages);

    Script(const YAML::Node& root);
    Script(const YAML::Node& root, PackagePtrMap packages);

    ~Script();

    int main(const std::vector<std::string>& argv);

    Value callFunction(const std::string& name, std::vector<Value> params);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu