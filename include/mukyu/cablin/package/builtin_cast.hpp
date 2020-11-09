#include <mukyu/cablin/core/package.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace package {


const std::string BUILTIN_OP_NAME = "cast";

class BuiltinCastPackage : public mukyu::cablin::core::Package {
public:
    BuiltinCastPackage();
    ~BuiltinCastPackage();

    void prepare(mukyu::cablin::core::Controller* controller);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace package
}  // namespace cablin
}  // namespace mukyu