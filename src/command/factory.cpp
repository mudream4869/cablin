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


mccore::CommandPtr createCommand(const mccore::ConfigPtr& node) {
    auto key = mccommon::getSingleKey(node);
    if (!key) {
        throw mccore::CablinParsingException(
            "createCommand: node must be single-key-map", node->path());
    }

    auto nodeValue = node->at(key.value());

    if (key == COMMANDVAR_KEY) {
        return std::make_unique<CommandVar>(nodeValue);
    } else if (key == COMMANDCALL_KEY) {
        return std::make_unique<CommandCall>(nodeValue);
    } else if (key == COMMANDASSIGN_KEY) {
        return std::make_unique<CommandAssign>(nodeValue);
    } else if (key == COMMANDBLOCK_KEY) {
        return std::make_unique<CommandBlock>(nodeValue);
    } else if (key == COMMANDIF_KEY) {
        return std::make_unique<CommandIf>(nodeValue);
    } else if (key == COMMANDWHILE_KEY) {
        return std::make_unique<CommandWhile>(nodeValue);
    } else if (key == COMMANDBREAK_KEY) {
        return std::make_unique<CommandBreak>();
    } else if (key == COMMANDCONTINUE_KEY) {
        return std::make_unique<CommandContinue>();
    } else if (key == COMMANDRETURN_KEY) {
        return std::make_unique<CommandReturn>(nodeValue);
    }

    throw mccore::CablinParsingException(
        "createCommand: cannot specify command: " + key.value(),
        node->path());
}

std::vector<mccore::CommandPtr> createCommandList(
    const mccore::ConfigPtr& node) {
    if (!node) {
        return {};
    }

    size_t sz = node->size();
    std::vector<mccore::CommandPtr> ret;

    for (size_t i = 0; i < sz; ++i) {
        ret.emplace_back(createCommand(node->at(i)));
    }
    return ret;
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu