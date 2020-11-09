#pragma once

#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <memory>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace function {


class FunctionInt : public mukyu::cablin::core::Function {
public:
    FunctionInt() = default;
    ~FunctionInt() = default;

    const std::string& getName() const {
        return name_;
    }

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller*,
        std::vector<mukyu::cablin::core::Value> params) {
        if (params.size() != 1) {
            throw std::runtime_error("FunctionInt: params size should be 1");
        }
        return params[0].cast<int>();
    }

private:
    std::string name_ = "int";
};

class FunctionInt64 : public mukyu::cablin::core::Function {
public:
    FunctionInt64() = default;
    ~FunctionInt64() = default;

    const std::string& getName() const {
        return name_;
    }

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller*,
        std::vector<mukyu::cablin::core::Value> params) {
        if (params.size() != 1) {
            throw std::runtime_error("FunctionInt64: params size should be 1");
        }
        return params[0].cast<int64_t>();
    }

private:
    std::string name_ = "int64";
};

class FunctionFloat : public mukyu::cablin::core::Function {
public:
    FunctionFloat() = default;
    ~FunctionFloat() = default;

    const std::string& getName() const {
        return name_;
    }

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller*,
        std::vector<mukyu::cablin::core::Value> params) {
        if (params.size() != 1) {
            throw std::runtime_error("FunctionFloat: params size should be 1");
        }
        return params[0].cast<float>();
    }

private:
    std::string name_ = "float";
};


}  // namespace function
}  // namespace cablin
}  // namespace mukyu