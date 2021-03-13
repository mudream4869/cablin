#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/value.hpp>

#include <optional>
#include <string>


namespace mukyu {
namespace cablin {
namespace common {


inline std::optional<std::string> getSingleKey(
    const mukyu::cablin::core::ConfigPtr& node) {
    if (!node->isMap() || node->size() != 1) {
        return {};
    }

    return node->keys()[0];
}

mukyu::cablin::core::Value valueNodeToValue(
    mukyu::cablin::core::ValueType type,
    const mukyu::cablin::core::ConfigPtr& valueNode);


}  // namespace common
}  // namespace cablin
}  // namespace mukyu
