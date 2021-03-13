#pragma once

#include <mukyu/cablin/core/config.hpp>
#include <mukyu/cablin/core/package.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace package {


class UserPackage : public mukyu::cablin::core::Package {
public:
    UserPackage(const std::string& name,
                const mukyu::cablin::core::ConfigPtr& root);

    ~UserPackage();

    void prepare(mukyu::cablin::core::Controller* controller);

    std::string name() const;

    std::vector<std::string> usePackages() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace package
}  // namespace cablin
}  // namespace mukyu