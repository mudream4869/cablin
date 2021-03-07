#include <mukyu/cablin/function/node.hpp>

#include <mukyu/cablin/command/factory.hpp>
#include <mukyu/cablin/command/flow.hpp>

#include <mukyu/cablin/core/command.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/value.hpp>
#include <mukyu/cablin/core/error.hpp>

#include <memory>
#include <string>


namespace mukyu {
namespace cablin {
namespace function {


namespace mccore = mukyu::cablin::core;
namespace mccmd = mukyu::cablin::command;


class FunctionNode::Impl {
private:
    struct Parameter {
        std::string name;
        mccore::ValueType type;
    };

public:
    Impl(const YAML::Node& node)
        : name_(node["name"].as<std::string>()),
          body_(mccmd::createCommandList(node["body"])) {
        const auto& params = node["params"];
        if (params != nullptr) {
            for (const auto& item : params) {
                Parameter param;
                param.name = item["name"].as<std::string>();
                param.type = mccore::STR_VALUETYPE_MAP.at(
                    item["type"].as<std::string>());

                params_.push_back(std::move(param));
            }
        }

        const auto& returnType = node["return_type"];
        if (returnType != nullptr) {
            returnType_ =
                mccore::STR_VALUETYPE_MAP.at(returnType.as<std::string>());
        }
    }

    ~Impl() = default;

    const std::string& getName() const {
        return name_;
    }

    mccore::Value execute(mccore::Controller* controller,
                          mccore::ValueList params) {
        if (params.size() != params_.size()) {
            throw mccore::CablinRuntimeException(
                "FunctionNode::Impl: number of parameters not equal");
        }

        for (size_t i = 0; i < params_.size(); ++i) {
            const auto& p = params_[i];
            if (p.type != params[i].type()) {
                throw mccore::CablinRuntimeException(
                    "FunctionNode::Impl: " + std::to_string(i) +
                    "parameters type not equal");
            }

            controller->addLocalVar(p.name, params[i]);
        }

        try {
            for (const auto& cmdPtr : body_) {
                cmdPtr->execute(controller);
            }
        } catch (const mccmd::ReturnException& rex) {
            return rex.returnValue;
        } catch (mccmd::LoopFlowControlException) {
            throw mccore::CablinRuntimeException(
                "FunctionNode::Impl: catch loop flow control");
        }

        // return zero-value;
        mccore::Value var(returnType_);
        return var;
    }

private:
    mccore::ValueType returnType_ = mccore::ValueType::NONE;
    std::string name_;
    std::vector<mccore::CommandPtr> body_;
    std::vector<Parameter> params_;
};


FunctionNode::FunctionNode(const YAML::Node& node)
    : impl_(std::make_unique<Impl>(node)) {
}

FunctionNode::~FunctionNode() = default;

const std::string& FunctionNode::getName() const {
    return impl_->getName();
}

mccore::Value FunctionNode::execute(mccore::Controller* controller,
                                    mccore::ValueList params) {
    return impl_->execute(controller, params);
}


}  // namespace function
}  // namespace cablin
}  // namespace mukyu