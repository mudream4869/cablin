#include <mukyu/cablin/config/yamlconfig.hpp>

#include <mukyu/cablin/core/script.hpp>

namespace mccore = mukyu::cablin::core;
namespace mcconf = mukyu::cablin::config;

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

    auto conf = mcconf::createYAMLConfigFromString(body);

    mccore::Script script(".");
    script.addYamlNode("main", conf);

    script.callFunction("main", "hello_world", {});
    return 0;
}