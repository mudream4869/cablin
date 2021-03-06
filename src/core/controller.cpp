#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/common/defer.hpp>

#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>


namespace mukyu {
namespace cablin {
namespace core {


namespace {


using VariableMap = std::unordered_map<std::string, Value>;
using FunctionMap = std::unordered_map<std::string, std::shared_ptr<Function>>;

class PackageController {
public:
    PackageController() = default;
    ~PackageController() = default;

    void addVar(const std::string& name, const Value& value) {
        if (globalVars_.find(name) != globalVars_.end()) {
            throw CablinRuntimeException("PackageController::addVar: " + name +
                                         " redefine found");
        }

        globalVars_[name] = value;
    }

    void setVar(const std::string& name, const Value& value) {
        auto varIt = globalVars_.find(name);
        if (varIt == globalVars_.end()) {
            throw CablinIdentifierNotFoundException(
                "PackageController::setVar: " + name + " not found");
        }

        if (varIt->second.type() != value.type()) {
            throw CablinRuntimeException(
                "PackageController::setVar: type not equal");
        }

        varIt->second = value;
    }

    const Value& getVar(const std::string& name) const {
        if (globalVars_.find(name) == globalVars_.end()) {
            throw CablinIdentifierNotFoundException(
                "PackageController::getVar: " + name + " not found");
        }

        return globalVars_.at(name);
    }

    void addFunction(std::shared_ptr<Function> function) {
        const auto& name = function->getName();
        if (funcs_.find(name) != funcs_.end()) {
            throw CablinRuntimeException(
                "PackageController::addFunction: " + name + " redefine found");
        }

        funcs_[name] = std::move(function);
    }

    Value callFunction(Controller* controller, const std::string& name,
                       std::vector<Value> params) {
        const auto& node = funcs_.find(name);
        if (node == funcs_.end()) {
            throw CablinIdentifierNotFoundException(
                "PackageController::callFunction: " + name + " not found");
        }

        return node->second->execute(controller, params);
    }


private:
    VariableMap globalVars_;
    FunctionMap funcs_;
};


struct BlockStack {
    std::vector<VariableMap> variableMap;
    std::string package;

    explicit BlockStack(const std::string& pkg) {
        package = pkg;
        variableMap.push_back({});
    }
};


class LocalStateController {
public:
    LocalStateController() {
        // XXX: A function block is prepared default. Is it make sense ???
        funcStack_.push(BlockStack(""));
    }

    ~LocalStateController() = default;

    void addVar(const std::string& name, const Value& value) {
        auto& vars = funcStack_.top().variableMap.back();

        if (vars.find(name) != vars.end()) {
            throw CablinRuntimeException(
                "LocalStateController::addVar: " + name + " redefine found");
        }

        vars[name] = value;
    }

    void setVar(const std::string& name, const Value& value) {
        auto& bStk = funcStack_.top().variableMap;

        for (auto it = bStk.rbegin(); it != bStk.rend(); ++it) {
            auto varIt = it->find(name);
            if (varIt == it->end()) {
                continue;
            }

            if (varIt->second.type() != value.type()) {
                throw CablinRuntimeException(
                    "LocalStateController::setVar: type not equal");
            }

            varIt->second = value;
            return;
        }

        throw CablinIdentifierNotFoundException(
            "LocalStateController::setVar: " + name + " not found");
    }

    const Value& getVar(const std::string& name) const {
        auto& bStk = funcStack_.top().variableMap;

        for (auto it = bStk.crbegin(); it != bStk.crend(); ++it) {
            if (it->find(name) != it->end()) {
                return it->at(name);
            }
        }

        throw CablinIdentifierNotFoundException(
            "LocalStateController::getVar: " + name + " not found");
    }

    std::string getCurrentPackageName() const {
        return funcStack_.top().package;
    }

    void pushFunctionBlock(const std::string& packageName) {
        funcStack_.push(BlockStack(packageName));
    }

    void popFunctionBlock() {
        funcStack_.pop();
    }

    void pushLocalBlock() {
        funcStack_.top().variableMap.push_back({});
    }

    void popLocalBlock() {
        funcStack_.top().variableMap.pop_back();
    }

private:
    std::stack<BlockStack> funcStack_;
};


}  // namespace


class Controller::Impl {
public:
    Impl() = default;
    ~Impl() = default;

    void addPackage(const std::string& package) {
        if (packages_.find(package) != packages_.end()) {
            throw CablinRuntimeException("Impl::addPackage: package " +
                                         package + " redefine");
        }
        packages_[package] = {};
    }

    void addPackageVar(const std::string& package, const std::string& name,
                       const Value& value) {
        if (packages_.find(package) == packages_.end()) {
            throw CablinIdentifierNotFoundException(
                "Impl::addPackageVar: package " + package + " not found");
        }
        packages_.at(package).addVar(name, value);
    }

    void setPackageVar(const std::string& package, const std::string& name,
                       const Value& value) {
        if (packages_.find(package) == packages_.end()) {
            throw CablinIdentifierNotFoundException(
                "Impl::setPackageVar: package " + package + " not found");
        }
        packages_.at(package).setVar(name, value);
    }

    const Value& getPackageVar(const std::string& package,
                               const std::string& name) {
        if (packages_.find(package) == packages_.end()) {
            throw CablinIdentifierNotFoundException(
                "Impl::getPackageVar: package " + package + " not found");
        }
        return packages_.at(package).getVar(name);
    }

    std::string getCurrentPackageName() const {
        return localStateContr_.getCurrentPackageName();
    }

    void addLocalVar(const std::string& name, const Value& value) {
        localStateContr_.addVar(name, value);
    }

    void setLocalVar(const std::string& name, const Value& value) {
        localStateContr_.setVar(name, value);
    }

    const Value& getLocalVar(const std::string& name) const {
        return localStateContr_.getVar(name);
    }

    void addFunction(const std::string& package,
                     std::shared_ptr<Function> function) {
        packages_.at(package).addFunction(std::move(function));
    }

    Value callFunction(Controller* controller, const std::string& packageName,
                       const std::string& name, std::vector<Value> params) {
        auto& package = packages_.at(packageName);

        localStateContr_.pushFunctionBlock(packageName);
        mukyu::cablin::common::Defer deferFunc(
            [this]() { this->localStateContr_.popFunctionBlock(); });

        return package.callFunction(controller, name, params);
    }

    void pushLocalBlock() {
        localStateContr_.pushLocalBlock();
    }

    void popLocalBlock() {
        localStateContr_.popLocalBlock();
    }

private:
    LocalStateController localStateContr_;
    std::unordered_map<std::string, PackageController> packages_;
};


Controller::Controller() : impl_(std::make_unique<Impl>()) {
}

Controller::~Controller() = default;


void Controller::addPackage(const std::string& package) {
    impl_->addPackage(package);
}

void Controller::addPackageVar(const std::string& package,
                               const std::string& name, const Value& value) {
    impl_->addPackageVar(package, name, value);
}

void Controller::setPackageVar(const std::string& package,
                               const std::string& name, const Value& value) {
    impl_->setPackageVar(package, name, value);
}

const Value& Controller::getPackageVar(const std::string& package,
                                       const std::string& name) {
    return impl_->getPackageVar(package, name);
}

std::string Controller::getCurrentPackageName() const {
    return impl_->getCurrentPackageName();
}

void Controller::addLocalVar(const std::string& name, const Value& value) {
    impl_->addLocalVar(name, value);
}

void Controller::setLocalVar(const std::string& name, const Value& value) {
    impl_->setLocalVar(name, value);
}

const Value& Controller::getLocalVar(const std::string& name) const {
    return impl_->getLocalVar(name);
}

void Controller::addFunction(const std::string& package,
                             std::shared_ptr<Function> function) {
    impl_->addFunction(package, std::move(function));
}

Value Controller::callFunction(const std::string& package,
                               const std::string& name,
                               const std::vector<Value>& params) {
    return impl_->callFunction(this, package, name, params);
}

void Controller::pushLocalBlock() {
    impl_->pushLocalBlock();
}

void Controller::popLocalBlock() {
    impl_->popLocalBlock();
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu