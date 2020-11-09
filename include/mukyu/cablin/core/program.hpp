#pragma once

#include <vector>
#include <string>
#include <memory>


namespace mukyu {
namespace cablin {
namespace core {


class Program final {
public:
    Program(const std::string& filename);
    ~Program();

    int execute(const std::vector<std::string>& argv);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu