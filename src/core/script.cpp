#include <mukyu/cablin/core/script.hpp>

#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/package/factory.hpp>
#include <mukyu/cablin/package/userdefine.hpp>
#include <mukyu/cablin/config/yamlconfig.hpp>


#include <vector>
#include <queue>
#include <filesystem>


namespace mukyu {
namespace cablin {
namespace core {


namespace mcpkg = mukyu::cablin::package;
namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;


const std::string MAINFUNCTION_NAME = "main";
const std::string YAML_FILEEXT = ".yaml";

class Script::Impl {
public:
    Impl(const std::string& importDir) : importDir_(importDir){};

    ~Impl() = default;

    void addFile(const std::string& filename) {
        auto stem = std::filesystem::path(filename).stem();
        auto conf = mcconf::createYAMLConfigFromFile(filename);
        auto pkg = std::make_shared<mcpkg::UserPackage>(stem.string(), conf);
        addPackage(std::move(pkg));
    }

    void addFile(const std::string& name, const std::string& filename) {
        auto conf = mcconf::createYAMLConfigFromFile(filename);
        auto pkg = std::make_shared<mcpkg::UserPackage>(name, conf);
        addPackage(std::move(pkg));
    }

    void addYamlNode(const std::string& name, const mccore::ConfigPtr& root) {
        auto pkg = std::make_shared<mcpkg::UserPackage>(name, root);
        addPackage(std::move(pkg));
    }

    void addPackage(PackagePtr package) {
        auto name = package->name();
        if (packageMap_.find(name) != packageMap_.end()) {
            return;
        }

        packageMap_.emplace(package->name(), package);
        for (auto name : package->usePackages()) {
            addPackage(name);
        }
    }

    void addPackage(const std::string& name) {
        if (packageMap_.find(name) != packageMap_.end()) {
            return;
        }

        PackagePtr pkg;
        try {
            pkg = mcpkg::createBuiltinPackage(name);
        } catch (const CablinIdentifierNotFoundException&) {
            auto conf = mcconf::createYAMLConfigFromFile(name + YAML_FILEEXT);
            pkg = std::make_shared<mcpkg::UserPackage>(name, conf);
        }

        addPackage(std::move(pkg));
    }

    Value callFunction(const std::string& packageName,
                       const std::string& functionName,
                       std::vector<Value> params) {
        Controller controller;
        for (auto p : packageMap_) {
            p.second->prepare(&controller);
        }

        return controller.callFunction(packageName, functionName, params);
    }

private:
    std::string importDir_;
    std::unordered_map<std::string, PackagePtr> packageMap_;
};

Script::Script(const std::string& importDir)
    : impl_(std::make_unique<Impl>(importDir)) {
}

Script::~Script() = default;

void Script::addFile(const std::string& name, const std::string& filename) {
    impl_->addFile(name, filename);
}

void Script::addFile(const std::string& filename) {
    impl_->addFile(filename);
}

void Script::addYamlNode(const std::string& name,
                         const mukyu::cablin::core::ConfigPtr& root) {
    impl_->addYamlNode(name, root);
}

void Script::addPackage(PackagePtr package) {
    impl_->addPackage(std::move(package));
}

Value Script::callFunction(const std::string& packageName,
                           const std::string& functionName,
                           std::vector<Value> argv) {
    return impl_->callFunction(packageName, functionName, argv);
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu