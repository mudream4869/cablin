#include <mukyu/cablin/core/program.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/package/builtin_io.hpp>
#include <mukyu/cablin/package/builtin_op.hpp>
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

class Program::Impl {
public:
    Impl(const std::string& filename) {
        // BFS all used packages
        packageMap_.emplace(MAINPACKAGE, std::make_shared<mcpkg::UserPackage>(
                                             MAINPACKAGE, filename));
        auto& mainPackage = packageMap_.at(MAINPACKAGE);
        mainPackage->prepare(&controller);

        std::queue<std::string> toLoad;
        for (const auto& pName : mainPackage->usePackages()) {
            toLoad.push(pName);
        }

        auto mainDir = std::filesystem::path(filename).parent_path();

        while (!toLoad.empty()) {
            auto pName = toLoad.front();
            toLoad.pop();

            if (packageMap_.find(pName) != packageMap_.end()) {
                continue;
            }

            if (pName == mcpkg::BUILTIN_IO_NAME) {
                packageMap_.emplace(
                    pName, std::make_shared<mcpkg::BuiltinIOPackage>());
            } else if (pName == mcpkg::BUILTIN_OP_NAME) {
                packageMap_.emplace(
                    pName, std::make_shared<mcpkg::BuiltinOperatorPackage>());
            } else {
                auto fullPath = (mainDir / (pName + YAML_FILEEXT)).string();
                packageMap_.emplace(pName, std::make_shared<mcpkg::UserPackage>(
                                               pName, fullPath));
            }


            auto& p = packageMap_.at(pName);

            p->prepare(&controller);
            for (const auto& opName : p->usePackages()) {
                toLoad.push(opName);
            }
        }
    }

    ~Impl() = default;

    int execute(const std::vector<std::string>& argv) {
        // default return 0 in only main function
        auto exitCode =
            controller.callFunction(MAINPACKAGE, MAINFUNCTION_NAME, {});

        if (exitCode.type() == ValueType::INT) {
            return exitCode.as<int>();
        }

        return 0;
    }

private:
    Controller controller;
    std::unordered_map<std::string, std::shared_ptr<Package>> packageMap_;
};

Program::Program(const std::string& filename)
    : impl_(std::make_unique<Impl>(filename)) {
}

Program::~Program() = default;

int Program::execute(const std::vector<std::string>& argv) {
    return impl_->execute(argv);
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu