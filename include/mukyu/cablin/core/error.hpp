#pragma once

#include <stdexcept>
#include <string>

#include <yaml-cpp/yaml.h>


namespace mukyu {
namespace cablin {
namespace core {


class CablinParsingException : public std::runtime_error {
public:
    CablinParsingException(const std::string& msg, int line, int pos,
                           int column)
        : std::runtime_error(msg), column(column), line(line), pos(pos) {
    }
    ~CablinParsingException() = default;

    int line;
    int pos;
    int column;
};

class CablinRuntimeException : public std::runtime_error {
public:
    CablinRuntimeException(const std::string& msg) : std::runtime_error(msg) {
    }
    ~CablinRuntimeException() = default;
};

class CablinIdentifierNotFoundException : public std::out_of_range {
public:
    CablinIdentifierNotFoundException(const std::string& msg)
        : std::out_of_range(msg) {
    }
    ~CablinIdentifierNotFoundException() = default;
};

inline CablinParsingException makeParsingException(const std::string& msg,
                                                   const YAML::Mark& mark) {
    return CablinParsingException(msg, mark.line, mark.pos, mark.column);
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu