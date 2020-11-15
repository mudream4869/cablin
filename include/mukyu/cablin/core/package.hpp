#pragma once

#include <string>
#include <vector>
#include <memory>

namespace mukyu {
namespace cablin {
namespace core {


class Controller;

class Package {
public:
    Package() = default;
    virtual ~Package() = default;

    // prepare package's functions and variable
    virtual void prepare(Controller*) = 0;

    // usePackages return imported package
    virtual std::vector<std::string> usePackages() const {
        return {};
    };
};

using PackagePtr = std::shared_ptr<Package>;


}  // namespace core
}  // namespace cablin
}  // namespace mukyu