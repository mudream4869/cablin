#include <mukyu/cablin/command/if.hpp>

#include <mukyu/cablin/command/factory.hpp>

#include <mukyu/cablin/common/defer.hpp>

#include <mukyu/cablin/expr/factory.hpp>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


class CommandIf::Impl {
public:
    Impl(const YAML::Node& node)
        : cond_(mcexpr::createExpr(node["condition"])),
          thenBody_(createCommandList(node["then"])),
          elseBody_(createCommandList(node["else"])) {
    }

    mccore::Value execute(mccore::Controller* controller) {
        controller->pushLocalBlock();
        mccommon::Defer defer([controller]() { controller->popLocalBlock(); });
        if (cond_->compute(controller).as<bool>()) {
            for (const auto& cmd : thenBody_) {
                cmd->execute(controller);
            }
        } else {
            for (const auto& cmd : elseBody_) {
                cmd->execute(controller);
            }
        }
        return {};
    }

private:
    mccore::ExprPtr cond_;
    std::vector<mccore::CommandPtr> thenBody_;
    std::vector<mccore::CommandPtr> elseBody_;
};

CommandIf::CommandIf(const YAML::Node& node)
    : impl_(std::make_unique<Impl>(node)) {
}

CommandIf::~CommandIf() = default;

mccore::Value CommandIf::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu