#pragma once

#include <string>
#include <utility>


namespace mukyu {
namespace cablin {
namespace common {


// splitPackage parse:
//
//   <package>::<name> => (<package>, <name>)
//
//   <name> => ("", name)
inline std::pair<std::string_view, std::string_view> splitPackage(
    std::string_view source) {
    auto pos = source.find("::");
    if (pos == std::string::npos) {
        return {{}, source};
    }

    return {source.substr(0, pos), source.substr(pos + 2)};
}


}  // namespace common
}  // namespace cablin
}  // namespace mukyu