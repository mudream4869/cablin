#pragma once

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <string>
#include <functional>


namespace mukyu {
namespace cablin {
namespace function {


class FunctionFunctor : public mukyu::cablin::core::Function {
public:
    using FunctorType = std::function<mukyu::cablin::core::Value(
        mukyu::cablin::core::ValueList)>;

    FunctionFunctor(const std::string& name, FunctorType functor)
        : name_(name), functor_(functor) {
    }

    ~FunctionFunctor() = default;

    const std::string& getName() const {
        return name_;
    }

    mukyu::cablin::core::Value execute(mukyu::cablin::core::Controller*,
                                       mukyu::cablin::core::ValueList params) {
        return functor_(params);
    }

private:
    std::string name_;
    FunctorType functor_;
};


}  // namespace function
}  // namespace cablin
}  // namespace mukyu