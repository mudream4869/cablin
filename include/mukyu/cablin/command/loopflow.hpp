#pragma once

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/command/flow.hpp>


namespace mukyu {
namespace cablin {
namespace command {


const std::string COMMANDBREAK_KEY = "break";

class CommandBreak : public mukyu::cablin::core::Command {
public:
    CommandBreak() = default;

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller) {
        throw BreakException();
    }
};

const std::string COMMANDCONTINUE_KEY = "continue";

class CommandContinue : public mukyu::cablin::core::Command {
public:
    CommandContinue() = default;

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller) {
        throw ContinueException();
    }
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu