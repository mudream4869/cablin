#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <yaml-cpp/yaml.h>

#include <optional>
#include <string>


namespace mukyu {
namespace cablin {
namespace common {


inline std::optional<std::string> getSingleKey(const YAML::Node& node) {
    if (!node.IsMap() || node.size() != 1) {
        return {};
    }

    for (const auto& it : node) {
        return it.first.as<std::string>();
    }

    return {};
}

mukyu::cablin::core::Value valueNodeToValue(mukyu::cablin::core::ValueType type,
                                            const YAML::Node& valueNode);


}  // namespace common
}  // namespace cablin
}  // namespace mukyu
