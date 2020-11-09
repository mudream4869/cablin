#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <memory>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace core {


class Controller;

class Function {
public:
    Function() = default;
    virtual ~Function() = default;

    virtual const std::string& getName() const = 0;

    virtual Value execute(Controller* controller,
                          std::vector<Value> params) = 0;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu