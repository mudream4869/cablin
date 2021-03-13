#pragma once

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/core/config.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace command {


const std::string COMMANDGLOBALVAR_KEY = "var";

class CommandGlobalVar : public mukyu::cablin::core::Command {
public:
    CommandGlobalVar(const std::string& package,
                     const mukyu::cablin::core::ConfigPtr& node);

    ~CommandGlobalVar();

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu