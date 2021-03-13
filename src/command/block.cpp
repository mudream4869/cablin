#include <mukyu/cablin/command/block.hpp>

#include <mukyu/cablin/command/factory.hpp>

#include <mukyu/cablin/common/defer.hpp>

#include <mukyu/cablin/expr/factory.hpp>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


class CommandBlock::Impl {
public:
    Impl(const mccore::ConfigPtr& node) : body_(createCommandList(node)) {
    }

    mccore::Value execute(mccore::Controller* controller) {
        controller->pushLocalBlock();
        mccommon::Defer defer([controller]() { controller->popLocalBlock(); });
        for (const auto& cmd : body_) {
            cmd->execute(controller);
        }
        return {};
    }

private:
    std::vector<mccore::CommandPtr> body_;
};

CommandBlock::CommandBlock(const mccore::ConfigPtr& node)
    : impl_(std::make_unique<Impl>(node)) {
}

CommandBlock::~CommandBlock() = default;

mccore::Value CommandBlock::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu