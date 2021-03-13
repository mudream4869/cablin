#pragma once

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace command {


const std::string COMMANDCALL_KEY = "call";

class CommandCall : public mukyu::cablin::core::Command {
public:
    CommandCall(const mukyu::cablin::core::ConfigPtr& node);
    ~CommandCall();

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu