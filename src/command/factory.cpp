#include <mukyu/cablin/command/factory.hpp>

#include <mukyu/cablin/command/assign.hpp>
#include <mukyu/cablin/command/block.hpp>
#include <mukyu/cablin/command/call.hpp>
#include <mukyu/cablin/command/if.hpp>
#include <mukyu/cablin/command/loopflow.hpp>
#include <mukyu/cablin/command/return.hpp>
#include <mukyu/cablin/command/var.hpp>
#include <mukyu/cablin/command/while.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/common/yamlutil.hpp>

#include <stdexcept>
#include <iostream>
#include <optional>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;


mccore::CommandPtr createCommand(const std::string& package,
                                 const YAML::Node& node) {
    auto key = mccommon::getSingleKey(node);
    if (!key) {
        throw mccore::makeParsingException(
            "createCommand: node must be single-key-map", node.Mark());
    }

    const auto& nodeValue = node[key.value()];

    if (key == COMMANDVAR_KEY) {
        return std::make_unique<CommandVar>(nodeValue);
    } else if (key == COMMANDCALL_KEY) {
        return std::make_unique<CommandCall>(package, nodeValue);
    } else if (key == COMMANDASSIGN_KEY) {
        return std::make_unique<CommandAssign>(package, nodeValue);
    } else if (key == COMMANDBLOCK_KEY) {
        return std::make_unique<CommandBlock>(package, nodeValue);
    } else if (key == COMMANDIF_KEY) {
        return std::make_unique<CommandIf>(package, nodeValue);
    } else if (key == COMMANDWHILE_KEY) {
        return std::make_unique<CommandWhile>(package, nodeValue);
    } else if (key == COMMANDBREAK_KEY) {
        return std::make_unique<CommandBreak>();
    } else if (key == COMMANDCONTINUE_KEY) {
        return std::make_unique<CommandContinue>();
    } else if (key == COMMANDRETURN_KEY) {
        return std::make_unique<CommandReturn>(package, nodeValue);
    }

    throw mccore::makeParsingException(
        "createCommand: cannot specify command: " + key.value(), node.Mark());
}

std::vector<mccore::CommandPtr> createCommandList(const std::string& package,
                                                  const YAML::Node& node) {
    if (node == nullptr) {
        return {};
    }

    size_t sz = node.size();
    std::vector<mccore::CommandPtr> ret;

    for (size_t i = 0; i < sz; ++i) {
        ret.emplace_back(createCommand(package, node[i]));
    }
    return ret;
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu