#include <mukyu/cablin/command/while.hpp>

#include <mukyu/cablin/command/factory.hpp>
#include <mukyu/cablin/command/flow.hpp>

#include <mukyu/cablin/common/defer.hpp>

#include <mukyu/cablin/expr/factory.hpp>


namespace mukyu {
namespace cablin {
namespace command {


namespace mccore = mukyu::cablin::core;
namespace mccommon = mukyu::cablin::common;
namespace mcexpr = mukyu::cablin::expr;


class CommandWhile::Impl {
public:
    Impl(const YAML::Node& node)
        : cond_(mcexpr::createExpr(node["condition"])),
          body_(createCommandList(node["body"])) {
    }

    mccore::Value execute(mccore::Controller* controller) {
        controller->pushLocalBlock();
        mccommon::Defer defer([controller]() { controller->popLocalBlock(); });
        while (cond_->compute(controller).as<bool>()) {
            try {
                for (const auto& cmd : body_) {
                    cmd->execute(controller);
                }
            } catch (BreakException) {
                break;
            } catch (ContinueException) {
                continue;
            }
        }
        return {};
    }

private:
    mccore::ExprPtr cond_;
    std::vector<mccore::CommandPtr> body_;
};

CommandWhile::CommandWhile(const YAML::Node& node)
    : impl_(std::make_unique<Impl>(node)) {
}

CommandWhile::~CommandWhile() = default;

mccore::Value CommandWhile::execute(mccore::Controller* controller) {
    return impl_->execute(controller);
}


}  // namespace command
}  // namespace cablin
}  // namespace mukyu