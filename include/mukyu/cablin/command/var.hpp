#pragma once

#include <mukyu/cablin/core/command.hpp>

#include <yaml-cpp/yaml.h>

#include <memory>


namespace mukyu {
namespace cablin {
namespace command {


const std::string COMMANDVAR_KEY = "var";

class CommandVar : public mukyu::cablin::core::Command {
public:
    CommandVar(const YAML::Node& node);
    ~CommandVar();

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu