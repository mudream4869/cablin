#pragma once

#include <mukyu/cablin/core/package.hpp>

#include <memory>
#include <string>


namespace mukyu {
namespace cablin {
namespace package {


mukyu::cablin::core::PackagePtr createPackage(const std::string& name,
                                              const std::string& dir);


}  // namespace package
}  // namespace cablin
}  // namespace mukyu