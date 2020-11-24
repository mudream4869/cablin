#include <mukyu/cablin/core/script.hpp>
#include <mukyu/cablin/core/function.hpp>
#include <mukyu/cablin/core/package.hpp>
#include <mukyu/cablin/core/controller.hpp>
#include <mukyu/cablin/function/functor.hpp>

#include <iostream>

namespace mccore = mukyu::cablin::core;
namespace mcfunc = mukyu::cablin::function;

const std::string MYPACKAGE_NAME = "my";

class MyPackage : public mccore::Package {
public:
    MyPackage() = default;
    ~MyPackage() = default;

    void prepare(mccore::Controller* controller) {
        controller->addPackage(MYPACKAGE_NAME);

        auto printFunc = [](mccore::ValueList params) {
            for (const auto& param : params) {
                switch (param.type()) {
                case mccore::ValueType::BOOL:
                    if (param.as<bool>()) {
                        std::cout << "true\n";
                    } else {
                        std::cout << "false\n";
                    }
                    break;
                case mccore::ValueType::INT:
                    std::cout << param.as<int>() << "\n";
                    break;
                case mccore::ValueType::STRING:
                    std::cout << param.as<std::string>() << "\n";
                    break;
                case mccore::ValueType::NONE:
                    std::cout << "none\n";
                    break;
                default:
                    std::cout << "??\n";
                }
            }
            return 0;
        };
        controller->addFunction(
            MYPACKAGE_NAME,
            std::make_shared<mcfunc::FunctionFunctor>("print", printFunc));
    }

    std::string name() const {
        return MYPACKAGE_NAME;
    }
};


int main(int argc, char** argv) {
    std::string body = R"(
- import: my

- func:
    name: hello_world
    body:
      - call:
          name: my::print
          params:
            - const:
                type: string
                value: Hello world call from script!
)";

    auto node = YAML::Load(body);

    mccore::Script script(".");

    script.addPackage(std::make_shared<MyPackage>());
    script.addYamlNode("main", node);

    script.callFunction("main", "hello_world", {});
    return 0;
}