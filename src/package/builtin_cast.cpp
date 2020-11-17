#include <mukyu/cablin/package/builtin_cast.hpp>

#include <mukyu/cablin/core/controller.hpp>

#include <mukyu/cablin/function/cast.hpp>


namespace mukyu {
namespace cablin {
namespace package {


namespace mccore = mukyu::cablin::core;
namespace mcfunc = mukyu::cablin::function;


class BuiltinCastPackage::Impl {
public:
    Impl() {
        func_ = {
            std::make_shared<mcfunc::FunctionInt>(),
            std::make_shared<mcfunc::FunctionInt64>(),
            std::make_shared<mcfunc::FunctionFloat>(),
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
    const std::string name_ = BUILTIN_CAST_NAME;
    std::vector<std::shared_ptr<mccore::Function>> func_;
};


BuiltinCastPackage::BuiltinCastPackage() : impl_(std::make_unique<Impl>()) {
}

BuiltinCastPackage::~BuiltinCastPackage() = default;

void BuiltinCastPackage::prepare(mccore::Controller* controller) {
    impl_->prepare(controller);
}


}  // namespace package
}  // namespace cablin
}  // namespace mukyu