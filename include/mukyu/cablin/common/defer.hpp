#pragma once

#include <functional>
#include <stdexcept>
#include <iostream>


namespace mukyu {
namespace cablin {
namespace common {


class Defer {
public:
    explicit Defer(const std::function<void()>& func) : func_(func) {
    }

    Defer(Defer&&) = delete;
    Defer(const Defer&) = delete;
    Defer& operator=(Defer&&) = delete;
    Defer& operator=(const Defer&) = delete;

    ~Defer() {
        try {
            func_();
        } catch (const std::exception& ex) {
            std::cerr << "Defer::~Defer: " << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "Defer::~Defer: unknown exception" << std::endl;
        }
    }

private:
    std::function<void()> func_;
};


}  // namespace common
}  // namespace cablin
}  // namespace mukyu