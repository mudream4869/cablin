#pragma once

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <memory>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace function {


class FunctionPrint : public mukyu::cablin::core::Function {
public:
    FunctionPrint();
    ~FunctionPrint();

    const std::string& getName() const;

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller,
        std::vector<mukyu::cablin::core::Value> params);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace function
}  // namespace cablin
}  // namespace mukyu