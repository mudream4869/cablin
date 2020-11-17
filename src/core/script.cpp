#include <mukyu/cablin/core/script.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/package/factory.hpp>
#include <mukyu/cablin/package/userdefine.hpp>


#include <vector>
#include <queue>
#include <filesystem>


namespace mukyu {
namespace cablin {
namespace core {


namespace mcpkg = mukyu::cablin::package;


const std::string MAINPACKAGE = "main";
const std::string MAINFUNCTION_NAME = "main";
const std::string YAML_FILEEXT = ".yaml";

class Script::Impl {
public:
    Impl(const YAML::Node& root, PackagePtrMap packages)
        : prePackageMap_(std::move(packages)) {
        auto mainPkg = std::make_shared<mcpkg::UserPackage>(MAINPACKAGE, root);
        loadMainPackage(std::move(mainPkg), "");
    }

    Impl(const std::string& filename, PackagePtrMap packages)
        : prePackageMap_(std::move(packages)) {
        // BFS all used packages
        auto mainPkg =
            std::make_shared<mcpkg::UserPackage>(MAINPACKAGE, filename);
        auto mainDir = std::filesystem::path(filename).parent_path();
        loadMainPackage(std::move(mainPkg), mainDir);
    }

    Impl(const YAML::Node& root) {
        auto mainPkg = std::make_shared<mcpkg::UserPackage>(MAINPACKAGE, root);
        loadMainPackage(std::move(mainPkg), "");
    }

    Impl(const std::string& filename) {
        // BFS all used packages
        auto mainPkg =
            std::make_shared<mcpkg::UserPackage>(MAINPACKAGE, filename);
        auto mainDir = std::filesystem::path(filename).parent_path();
        loadMainPackage(std::move(mainPkg), mainDir);
    }

    ~Impl() = default;

    int main(const std::vector<std::string>& argv) {
        // default return 0 in only main function
        auto exitCode =
            controller_.callFunction(MAINPACKAGE, MAINFUNCTION_NAME, {});

        if (exitCode.type() == ValueType::INT) {
            return exitCode.as<int>();
        }

        return 0;
    }

    Value callFunction(const std::string& name, std::vector<Value> params) {
        return controller_.callFunction(MAINPACKAGE, name, params);
    }

private:
    void loadMainPackage(PackagePtr mainPackage,
                         const std::string& mainDirStr) {
        packageMap_.emplace(MAINPACKAGE, mainPackage);
        mainPackage->prepare(&controller_);

        std::queue<std::string> toLoad;
        for (const auto& pName : mainPackage->usePackages()) {
            toLoad.push(pName);
        }

        auto mainDir = std::filesystem::path(mainDirStr);

        while (!toLoad.empty()) {
            auto pName = toLoad.front();
            toLoad.pop();

            if (packageMap_.find(pName) != packageMap_.end()) {
                continue;
            }

            PackagePtr newPkg;

            if (prePackageMap_.find(pName) != prePackageMap_.end()) {
                newPkg = prePackageMap_.at(pName);
            } else {
                newPkg = mcpkg::createPackage(pName, mainDir);
            }

            packageMap_.emplace(pName, std::move(newPkg));

            auto& p = packageMap_.at(pName);

            p->prepare(&controller_);
            for (const auto& opName : p->usePackages()) {
                toLoad.push(opName);
            }
        }
    }

private:
    Controller controller_;
    PackagePtrMap prePackageMap_;
    PackagePtrMap packageMap_;
};

Script::Script(const std::string& filename)
    : impl_(std::make_unique<Impl>(filename)) {
}

Script::Script(const std::string& filename, PackagePtrMap packages)
    : impl_(std::make_unique<Impl>(filename, packages)) {
}

Script::Script(const YAML::Node& root) : impl_(std::make_unique<Impl>(root)) {
}

Script::Script(const YAML::Node& root, PackagePtrMap packages)
    : impl_(std::make_unique<Impl>(root, packages)) {
}

Script::~Script() = default;

int Script::main(const std::vector<std::string>& argv) {
    return impl_->main(argv);
}

Value Script::callFunction(const std::string& name, std::vector<Value> argv) {
    return impl_->callFunction(name, argv);
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu