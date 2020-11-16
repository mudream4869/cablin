#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <yaml-cpp/yaml.h>

#include <vector>
#include <string>
#include <memory>


namespace mukyu {
namespace cablin {
namespace core {


class Script final {
public:
    Script(const std::string& filename);

    Script(const YAML::Node& root);

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