#pragma once

#include <mukyu/cablin/core/config.hpp>

#include <optional>
#include <stdexcept>
#include <string>


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
};

class CablinIdentifierNotFoundException : public std::out_of_range {
public:
    explicit CablinIdentifierNotFoundException(const std::string& msg)
        : std::out_of_range(msg) {
    }
};

inline CablinParsingException makeParsingException(
    const std::string& msg,
    std::optional<mukyu::cablin::core::ConfigMark> maybeMark) {
    if (maybeMark) {
        auto mark = maybeMark.value();
        return CablinParsingException(msg, mark.line, mark.pos, mark.col);
    }
    return CablinParsingException(msg, 0, 0, 0);
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu