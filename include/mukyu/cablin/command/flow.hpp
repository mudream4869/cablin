#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <stdexcept>


namespace mukyu {
namespace cablin {
namespace command {


class LoopFlowControlException : public std::exception {
public:
    LoopFlowControlException() = default;
    virtual ~LoopFlowControlException() = default;
};

class BreakException : public LoopFlowControlException {
public:
    BreakException() = default;
    ~BreakException() = default;
};

class ContinueException : public LoopFlowControlException {
public:
    ContinueException() = default;
    ~ContinueException() = default;
};

class ReturnException : public std::exception {
public:
    mukyu::cablin::core::Value returnValue;

    ReturnException(mukyu::cablin::core::Value value) : returnValue(value) {
    }

    ~ReturnException() = default;
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu