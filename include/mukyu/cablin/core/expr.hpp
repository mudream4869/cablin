#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace core {


class Controller;

class Expr {
public:
    Expr() = default;
    virtual ~Expr() = default;
    virtual Value compute(Controller* controller) = 0;
};

using ExprPtr = std::unique_ptr<Expr>;


}  // namespace core
}  // namespace cablin
}  // namespace mukyu