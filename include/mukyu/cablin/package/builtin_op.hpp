#include <mukyu/cablin/core/package.hpp>

#include <memory>


namespace mukyu {
namespace cablin {
namespace package {


const std::string BUILTIN_OP_NAME = "op";

class BuiltinOperatorPackage : public mukyu::cablin::core::Package {
public:
    BuiltinOperatorPackage();
    ~BuiltinOperatorPackage();

    void prepare(mukyu::cablin::core::Controller* controller);

    std::string name() const {
        return BUILTIN_OP_NAME;
    }

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace package
}  // namespace cablin
}  // namespace mukyu