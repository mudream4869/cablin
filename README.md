# Cablin

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

![Cablin Logo](cablin.png)

A Cablin interpreter written in c-plus-plus.

## How to build and execute examples

```bash
# Build
mkdir build
cd build
cmake ..

# Execute example
example/example1
example/example2

# Execute interpreter
cd ../cablin_examples
../build/interpreter/interpreter test.yaml

```

## Use Cablin as an Embedding Script

### Hello world

Load the script and execute the `hello_world` function defined in script.

```cpp
#include <mukyu/cablin/core/script.hpp>

namespace mccore = mukyu::cablin::core;

int main(int argc, char** argv) {
    std::string body = R"(
- import: io

- func:
    name: hello_world
    body:
      - call:
          name: io::print
          params:
            - const:
                type: string
                value: Hello world!
)";

    auto node = YAML::Load(body);
    mccore::Script script(node);
    script.callFunction("hello_world", {});
    return 0;
}
```

### Call c++ function from Cablin script

[➡️ Complete code](example/example2.cpp)

```cpp
namespace mccore = mukyu::cablin::core;
namespace mcfunc = mukyu::cablin::function;

const std::string MYPACKAGE_NAME = "my";

class MyPackage : public mccore::Package {
public:
    MyPackage() = default;
    ~MyPackage() = default;

    // The prepare function register all the function and variable need in package
    void prepare(mccore::Controller* controller) {
        // Register package name
        controller->addPackage(MYPACKAGE_NAME);

        auto printFunc = [](mccore::ValueList params) {
            // ... 
        };
        
        // Register print function
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
    script.addYamlNode("main", node);
    script.addPackage(std::make_shared<MyPackage>());

    script.callFunction("main", "hello_world", {});
    return 0;
}
```

## Credits

* Created my free logo at [LogoMakr.com](https://logomakr.com).
