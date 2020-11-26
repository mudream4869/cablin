#pragma once

#include <mukyu/cablin/core/package.hpp>

#include <memory>
#include <string>


namespace mukyu {
namespace cablin {
namespace package {


mukyu::cablin::core::PackagePtr createBuiltinPackage(const std::string& name);


}  // namespace package
}  // namespace cablin
}  // namespace mukyu