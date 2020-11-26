#pragma once

#include <mukyu/cablin/core/command.hpp>

#include <memory>
#include <vector>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace command {


mukyu::cablin::core::CommandPtr createCommand(const YAML::Node& node);

std::vector<mukyu::cablin::core::CommandPtr> createCommandList(
    const YAML::Node& node);


}  // namespace command
}  // namespace cablin
}  // namespace mukyu