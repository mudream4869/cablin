#pragma once

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>


namespace mukyu {
namespace cablin {
namespace core {


// ConfigMark marked where config locate in a file
struct ConfigMark {
    int line;
    int pos;
    int col;
};

// ConfigTypeError is thrown when config type not match expectation
class ConfigTypeError : public std::runtime_error {
public:
    ConfigTypeError(const std::string& msg) : std::runtime_error(msg) {
    }
    ~ConfigTypeError() = default;
};

class Config;
using ConfigPtr = std::unique_ptr<Config>;

// Config class Provide a readonly tree structure config interface
class Config {
public:
    Config() = default;
    virtual ~Config() = default;

    // Return dict[key]
    // Throw ConfigTypeError if the type is not a Map
    virtual ConfigPtr at(const std::string& key) const = 0;

    // Return index_th element of list
    // Throw ConfigTypeError if the type is not a List
    virtual ConfigPtr at(size_t index) const = 0;

    // Return size of list or map
    // Throw ConfigTypeError if the type is not a List of a Map
    virtual size_t size() const = 0;

    // Return keys in a map
    // Throw ConfigTypeError if the type is not a Map
    virtual std::vector<std::string> keys() const = 0;

    // Return type checking result
    virtual bool isList() const = 0;
    virtual bool isMap() const = 0;
    virtual bool isScalar() const = 0;
    virtual bool isNull() const = 0;

    // When config is reading from a file,
    // Mark can help user to locate the config
    virtual std::optional<ConfigMark> getMark() const {
        return {};
    }

    // Read the config node as scalar T
    // support int, int64_t, std::string, float, bool
    template <typename T>
    T as() const;

protected:
    // asXXX is what as<T> really called
    // Throw ConfigTypeError if the type is not match
    virtual int asInt() const = 0;
    virtual int64_t asInt64() const = 0;
    virtual std::string asString() const = 0;
    virtual float asFloat() const = 0;
    virtual bool asBool() const = 0;
};

template <>
inline int Config::as<int>() const {
    return asInt();
}

template <>
inline int64_t Config::as<int64_t>() const {
    return asInt64();
}

template <>
inline std::string Config::as<std::string>() const {
    return asString();
}

template <>
inline float Config::as<float>() const {
    return asInt();
}

template <>
inline bool Config::as<bool>() const {
    return asBool();
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu
