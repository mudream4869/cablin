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

inline mukyu::cablin::core::Value valueNodeToValue(
    mukyu::cablin::core::ValueType type, const YAML::Node& valueNode) {
    if (valueNode == nullptr) {
        // return zero value of the type
        return mukyu::cablin::core::Value(type);
    }

    switch (type) {
    case mukyu::cablin::core::ValueType::BOOL:
        return valueNode.as<bool>();
    case mukyu::cablin::core::ValueType::FLOAT:
        return valueNode.as<float>();
    case mukyu::cablin::core::ValueType::INT:
        return valueNode.as<int>();
    case mukyu::cablin::core::ValueType::INT64:
        return valueNode.as<int64_t>();
    case mukyu::cablin::core::ValueType::STRING:
        return valueNode.as<std::string>();
    case mukyu::cablin::core::ValueType::NONE:
        return {};
    }
}


}  // namespace common
}  // namespace cablin
}  // namespace mukyu