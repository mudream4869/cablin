#pragma once

#include <mukyu/cablin/core/package.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace package {


class UserPackage : public mukyu::cablin::core::Package {
public:
    UserPackage(const std::string& name, const std::string& filename);
    ~UserPackage();

    void prepare(mukyu::cablin::core::Controller* controller);
    std::vector<std::string> usePackages() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace package
}  // namespace cablin
}  // namespace mukyu