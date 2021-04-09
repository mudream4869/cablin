#pragma once

#include <optional>
#include <stdexcept>
#include <string>


namespace mukyu {
namespace cablin {
namespace core {


class CablinParsingException : public std::runtime_error {
public:
    CablinParsingException(const std::string& msg, const std::string& path)
        : std::runtime_error(msg), path(path) {
    }

    ~CablinParsingException() = default;

    std::string path;
};

class CablinRuntimeException : public std::runtime_error {
public:
    explicit CablinRuntimeException(const std::string& msg)
        : std::runtime_error(msg) {
    }

    CablinRuntimeException(const std::string& msg, const std::string& path)
        : std::runtime_error(msg), path(path) {
    }

    ~CablinRuntimeException() = default;

    std::string path;
};

class CablinIdentifierNotFoundException : public std::out_of_range {
public:
    explicit CablinIdentifierNotFoundException(const std::string& msg)
        : std::out_of_range(msg) {
    }

    CablinIdentifierNotFoundException(const std::string& msg,
                                      const std::string& path)
        : std::out_of_range(msg), path(path) {
    }

    ~CablinIdentifierNotFoundException() = default;

    std::string path;
};


}  // namespace core
}  // namespace cablin
}  // namespace mukyu
