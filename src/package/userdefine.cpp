#include <mukyu/cablin/package/userdefine.hpp>

#include <mukyu/cablin/core/controller.hpp>

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
    Impl(const std::string& name, const std::string& filename) : name_(name) {
        auto root = YAML::LoadFile(filename);

        if (!root.IsSequence()) {
            throw std::runtime_error("Impl::Impl: should be a list");
        }

        for (const auto& it : root) {
            auto key = mccommon::getSingleKey(it);
            if (!key) {
                throw std::runtime_error(
                    "Impl::Impl: node must be single-key-map");
            }

            const auto& obj = it[key.value()];

            if (key == "func") {
                userFunc_.push_back(
                    std::make_shared<mcfunc::FunctionNode>(name_, obj));
            } else if (key == mccmd::COMMANDGLOBALVAR_KEY) {
                globalCommand_.push_back(
                    std::make_unique<mccmd::CommandGlobalVar>(name_, obj));
            } else if (key == "import") {
                usedPackages_.push_back(obj.as<std::string>());
            } else {
                throw std::runtime_error("Impl::Impl: " + key.value() +
                                         "not match any pacakge command");
            }
        }
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

    std::vector<std::string> usePackages() const {
        return usedPackages_;
    }

private:
    std::string name_;

    std::vector<std::string> usedPackages_;

    std::vector<mccore::CommandPtr> globalCommand_;
    std::vector<std::shared_ptr<mccore::Function>> userFunc_;
};

UserPackage::UserPackage(const std::string& name, const std::string& filename)
    : impl_(std::make_unique<Impl>(name, filename)) {
}

UserPackage::~UserPackage() = default;

void UserPackage::prepare(mccore::Controller* controller) {
    impl_->prepare(controller);
}

std::vector<std::string> UserPackage::usePackages() const {
    return impl_->usePackages();
}


}  // namespace package
}  // namespace cablin
}  // namespace mukyu