#include <mukyu/cablin/package/factory.hpp>

#include <mukyu/cablin/core/error.hpp>

#include <mukyu/cablin/package/builtin_cast.hpp>
#include <mukyu/cablin/package/builtin_io.hpp>
#include <mukyu/cablin/package/builtin_op.hpp>

#include <mukyu/cablin/package/userdefine.hpp>

#include <filesystem>


namespace mukyu {
namespace cablin {
namespace package {


namespace mccore = mukyu::cablin::core;
namespace mcpkg = mukyu::cablin::package;


const std::string YAML_FILEEXT = ".yaml";

mccore::PackagePtr createPackage(const std::string& name,
                                 const std::string& dir) {
    auto pathDir = std::filesystem::path(dir);

    if (name == mcpkg::BUILTIN_IO_NAME) {
        return std::make_shared<mcpkg::BuiltinIOPackage>();
    } else if (name == mcpkg::BUILTIN_OP_NAME) {
        return std::make_shared<mcpkg::BuiltinOperatorPackage>();
    } else if (name == mcpkg::BUILTIN_CAST_NAME) {
        return std::make_shared<mcpkg::BuiltinCastPackage>();
    } else {
        auto fullPath = (pathDir / (name + YAML_FILEEXT)).string();
        return std::make_shared<mcpkg::UserPackage>(name, fullPath);
    }

    throw mccore::CablinIdentifierNotFoundException("craetePackage: " + name +
                                                    " not found");
}


}  // namespace package
}  // namespace cablin
}  // namespace mukyu