#pragma once

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <yaml-cpp/yaml.h>

#include <memory>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace function {


class FunctionNode : public mukyu::cablin::core::Function {
public:
    FunctionNode(const std::string& package, const YAML::Node& node);

    ~FunctionNode();

    const std::string& getName() const;

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller,
        mukyu::cablin::core::ValueList params);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace function
}  // namespace cablin
}  // namespace mukyu