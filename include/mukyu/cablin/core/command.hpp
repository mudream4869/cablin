#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace core {


class Controller;

class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    virtual Value execute(Controller*) = 0;
};

using CommandPtr = std::unique_ptr<Command>;


}  // namespace core
}  // namespace cablin
}  // namespace mukyu