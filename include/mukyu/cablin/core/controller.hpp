#pragma once

#include <mukyu/cablin/core/value.hpp>

#include <memory>
#include <string>


namespace mukyu {
namespace cablin {
namespace core {


class Function;

class Controller final {
public:
    Controller();
    ~Controller();

    void addPackage(const std::string& package);

    void addPackageVar(const std::string& package, const std::string& name,
                       const Value& value);

    void setPackageVar(const std::string& package, const std::string& name,
                       const Value& value);

    const Value& getPackageVar(const std::string& package,
                               const std::string& name);

    void addLocalVar(const std::string& name, const Value& value);

    void setLocalVar(const std::string& name, const Value& value);

    const Value& getLocalVar(const std::string& name) const;

    void addFunction(const std::string& package,
                     std::shared_ptr<Function> function);

    Value callFunction(const std::string& package, const std::string& name,
                       const std::vector<Value>& params);

    void pushLocalBlock();

    void popLocalBlock();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu