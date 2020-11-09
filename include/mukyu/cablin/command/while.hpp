#pragma once

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace command {


const std::string COMMANDWHILE_KEY = "while";

class CommandWhile : public mukyu::cablin::core::Command {
public:
    CommandWhile(const std::string& package, const YAML::Node& node);
    ~CommandWhile();

    mukyu::cablin::core::Value execute(
        mukyu::cablin::core::Controller* controller);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace command
}  // namespace cablin
}  // namespace mukyu