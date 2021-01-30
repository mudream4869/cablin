#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/core/value.hpp>

#include <yaml-cpp/yaml.h>

#include <optional>
#include <string>


namespace mukyu {
namespace cablin {
namespace common {


namespace mccore = mukyu::cablin::core;


mccore::Value valueNodeToValue(mccore::ValueType type,
                               const YAML::Node& valueNode) {
    if (valueNode == nullptr) {
        // return zero value of the type
        return mccore::Value(type);
    }

    switch (type) {
    case mccore::ValueType::BOOL:
        return valueNode.as<bool>();
    case mccore::ValueType::FLOAT:
        return valueNode.as<float>();
    case mccore::ValueType::INT:
        return valueNode.as<int>();
    case mccore::ValueType::INT64:
        return valueNode.as<int64_t>();
    case mccore::ValueType::STRING:
        return valueNode.as<std::string>();
    case mccore::ValueType::NONE:
        return {};
    }

    std::string msg =
        "valueNodeToValue: " + std::to_string(static_cast<int>(type)) +
        " is not an value type";

    throw mccore::makeParsingException(msg, valueNode.Mark());
}


}  // namespace common
}  // namespace cablin
}  // namespace mukyu