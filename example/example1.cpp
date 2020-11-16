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