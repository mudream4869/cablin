#include <mukyu/cablin/package/userdefine.hpp>

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/command/globalvar.hpp>

#include <mukyu/cablin/common/yamlutil.hpp>

#include <mukyu/cablin/function/node.hpp>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace package {


namespace mccore = mukyu::cablin::core;
namespace mccmd = mukyu::cablin::command;
namespace mccommon = mukyu::cablin::common;
namespace mcfunc = mukyu::cablin::function;


class UserPackage::Impl {
public:
    Impl(const std::string& name, const mukyu::cablin::core::ConfigPtr& root)
        : name_(name) {
        loadNode(root);
    }

    ~Impl() = default;

    void prepare(mccore::Controller* controller) {
        controller->addPackage(name_);

        for (const auto& cmd : globalCommand_) {
            cmd->execute(controller);
        }

        for (const auto& func : userFunc_) {
            controller->addFunction(name_, func);
        }
    }

    std::string name() const {
        return name_;
    }

    std::vector<std::string> usePackages() const {
        return usedPackages_;
    }

private:
    void loadNode(const mukyu::cablin::core::ConfigPtr& root) {
        if (!root->isList()) {
            throw mccore::CablinParsingException(
                "Impl::loadNode: should be a list", root->path());
        }

        size_t size = root->size();
        for (size_t i = 0; i < size; ++i) {
            auto it = root->at(i);
            auto key = mccommon::getSingleKey(it);
            if (!key) {
                throw mccore::CablinParsingException(
                    "Impl::loadNode: node must be single-key-map",
                    it->path());
            }

            auto obj = it->at(key.value());

            if (key == "func") {
                userFunc_.push_back(
                    std::make_shared<mcfunc::FunctionNode>(obj));
            } else if (key == mccmd::COMMANDGLOBALVAR_KEY) {
                globalCommand_.push_back(
                    std::make_unique<mccmd::CommandGlobalVar>(name_, obj));
            } else if (key == "import") {
                usedPackages_.push_back(obj->as<std::string>());
            } else {
                throw mccore::CablinParsingException(
                    "Impl::loadNode: " + key.value() +
                        "not match any pacakge command",
                    it->path());
            }
        }
    }

private:
    std::string name_;

    std::vector<std::string> usedPackages_;

    std::vector<mccore::CommandPtr> globalCommand_;
    std::vector<std::shared_ptr<mccore::Function>> userFunc_;
};

UserPackage::UserPackage(const std::string& name,
                         const mukyu::cablin::core::ConfigPtr& root)
    : impl_(std::make_unique<Impl>(name, root)) {
}

UserPackage::~UserPackage() = default;

void UserPackage::prepare(mccore::Controller* controller) {
    impl_->prepare(controller);
}

std::string UserPackage::name() const {
    return impl_->name();
}

std::vector<std::string> UserPackage::usePackages() const {
    return impl_->usePackages();
}


}  // namespace package
}  // namespace cablin
}  // namespace mukyu