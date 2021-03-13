#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <memory>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace function {


class FunctionNode : public mukyu::cablin::core::Function {
public:
    FunctionNode(const mukyu::cablin::core::ConfigPtr& node);

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