#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <memory>
#include <string>
#include <vector>


namespace mukyu {
namespace cablin {
namespace core {


class Controller;

using ValueList = std::vector<Value>;

class Function {
public:
    Function() = default;
    virtual ~Function() = default;

    virtual const std::string& getName() const = 0;

    virtual Value execute(Controller* controller, ValueList params) = 0;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu