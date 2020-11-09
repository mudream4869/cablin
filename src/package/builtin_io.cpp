#include <mukyu/cablin/package/builtin_io.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/function/print.hpp>


namespace mukyu {
namespace cablin {
namespace package {


namespace mccore = mukyu::cablin::core;
namespace mcfunc = mukyu::cablin::function;


class BuiltinIOPackage::Impl {
public:
    Impl() {
        func_ = {
            std::make_shared<mcfunc::FunctionPrint>(),
        };
    }

    ~Impl() = default;

    void prepare(mccore::Controller* controller) {
        controller->addPackage(name_);

        for (const auto& func : func_) {
            controller->addFunction(name_, func);
        }
    }

private:
    const std::string name_ = BUILTIN_IO_NAME;
    std::vector<std::shared_ptr<mccore::Function>> func_;
};


BuiltinIOPackage::BuiltinIOPackage() : impl_(std::make_unique<Impl>()) {
}

BuiltinIOPackage::~BuiltinIOPackage() = default;

void BuiltinIOPackage::prepare(mccore::Controller* controller) {
    impl_->prepare(controller);
}


}  // namespace package
}  // namespace cablin
}  // namespace mukyu