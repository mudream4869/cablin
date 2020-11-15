#pragma once

#include <vector>
#include <string>
#include <memory>


namespace mukyu {
namespace cablin {
namespace core {


class Script final {
public:
    Script(const std::string& filename);
    ~Script();

    int execute(const std::vector<std::string>& argv);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu