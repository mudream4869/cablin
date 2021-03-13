#pragma once

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/core/config.hpp>

#include <memory>
#include <vector>


namespace mukyu {
namespace cablin {
namespace command {


mukyu::cablin::core::CommandPtr createCommand(
    const mukyu::cablin::core::ConfigPtr& node);

std::vector<mukyu::cablin::core::CommandPtr> createCommandList(
    const mukyu::cablin::core::ConfigPtr& node);


}  // namespace command
}  // namespace cablin
}  // namespace mukyu