#include <mukyu/cablin/package/factory.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/package/builtin_cast.hpp>
#include <mukyu/cablin/package/builtin_io.hpp>


namespace mukyu {
namespace cablin {
namespace package {


namespace mccore = mukyu::cablin::core;
namespace mcpkg = mukyu::cablin::package;


mccore::PackagePtr createBuiltinPackage(const std::string& name) {
    if (name == mcpkg::BUILTIN_IO_NAME) {
        return std::make_shared<mcpkg::BuiltinIOPackage>();
    } else if (name == mcpkg::BUILTIN_CAST_NAME) {
        return std::make_shared<mcpkg::BuiltinCastPackage>();
    }
    throw mccore::CablinIdentifierNotFoundException("createPackage: " + name +
                                                    " is not builtin package");
}


}  // namespace package
}  // namespace cablin
}  // namespace mukyu