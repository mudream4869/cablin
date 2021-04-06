#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

#include <mukyu/cablin/core/error.hpp>


namespace mukyu {
namespace cablin {
namespace core {


enum class ValueType {
    NONE,
    BOOL,
    INT,
    INT64,
    FLOAT,
    STRING,
};

const std::unordered_map<std::string, ValueType> STR_VALUETYPE_MAP = {
    {"none", ValueType::NONE},   {"bool", ValueType::BOOL},
    {"int", ValueType::INT},     {"int64", ValueType::INT64},
    {"float", ValueType::FLOAT}, {"string", ValueType::STRING},
};

const std::unordered_map<ValueType, std::string> VALUETYPE_STR_MAP = {
    {ValueType::NONE, "none"},   {ValueType::BOOL, "bool"},
    {ValueType::INT, "int"},     {ValueType::INT64, "int64"},
    {ValueType::FLOAT, "float"}, {ValueType::STRING, "string"},
};

class Value final {
public:
    Value(int v) noexcept : iv_(v), type_(ValueType::INT) {
    }

    Value(bool v) noexcept : bv_(v), type_(ValueType::BOOL) {
    }

    Value(int64_t v) noexcept : i64v_(v), type_(ValueType::INT64) {
    }

    Value(float v) noexcept : fv_(v), type_(ValueType::FLOAT) {
    }

    Value(const std::string& v) : strv_(v), type_(ValueType::STRING) {
    }

    Value(ValueType type) noexcept : type_(type) {
    }

    Value() noexcept = default;
    ~Value() noexcept = default;

    ValueType type() const noexcept {
        return type_;
    }

    template <typename T>
    T as() const;

    template <typename T>
    Value cast() const;

private:
    ValueType type_ = ValueType::NONE;
    bool bv_ = false;
    int iv_ = 0;
    int64_t i64v_ = 0;
    float fv_ = 0;
    std::string strv_;
};

template <>
inline int Value::as() const {
    if (type_ != ValueType::INT) {
        throw CablinRuntimeException("Value::as: type is not int");
    }
    return iv_;
}

template <>
inline int64_t Value::as() const {
    if (type_ != ValueType::INT64) {
        throw CablinRuntimeException("Value::as: type is not int64");
    }
    return i64v_;
}

template <>
inline float Value::as() const {
    if (type_ != ValueType::FLOAT) {
        throw CablinRuntimeException("Value::as: type is not float");
    }
    return fv_;
}

template <>
inline bool Value::as() const {
    if (type_ != ValueType::BOOL) {
        throw CablinRuntimeException("Value::as: type is not bool");
    }
    return bv_;
}

template <>
inline std::string Value::as() const {
    if (type_ != ValueType::STRING) {
        throw CablinRuntimeException("Value::as: type is not string");
    }
    return strv_;
}

template <>
inline Value Value::cast<int>() const {
    switch (type_) {
    case ValueType::INT:
        return *this;
    case ValueType::INT64:
        return static_cast<int>(this->i64v_);
    case ValueType::FLOAT:
        return static_cast<int>(this->fv_);
    default:
        throw CablinRuntimeException("Value::cast<int>: type is not numerical");
    }
}

template <>
inline Value Value::cast<int64_t>() const {
    switch (type_) {
    case ValueType::INT:
        return static_cast<int>(this->iv_);
    case ValueType::INT64:
        return *this;
    case ValueType::FLOAT:
        return static_cast<int64_t>(this->fv_);
    default:
        throw CablinRuntimeException(
            "Value::cast<int64_t>: type is not numerical");
    }
}

template <>
inline Value Value::cast<float>() const {
    switch (type_) {
    case ValueType::INT:
        return static_cast<float>(this->iv_);
    case ValueType::INT64:
        return static_cast<float>(this->i64v_);
    case ValueType::FLOAT:
        return *this;
    default:
        throw CablinRuntimeException(
            "Value::cast<float>: type is not numerical");
    }
}

inline Value operator+(const Value& v1, const Value& v2) {
    if (v1.type() != v2.type()) {
        throw CablinRuntimeException("Value::operator+: type of v1 and v2 not equal");
    }

    switch (v1.type()) {
    case ValueType::FLOAT:
        return v1.as<float>() + v2.as<float>();
    case ValueType::INT:
        return v1.as<int>() + v2.as<int>();
    case ValueType::INT64:
        return v1.as<int64_t>() + v2.as<int64_t>();
    case ValueType::STRING:
        return v1.as<std::string>() + v2.as<std::string>();
    default:
        throw CablinRuntimeException("Value::operator+: type of v1 and v2 cannot apply +");
    }
}

inline Value operator-(const Value& v1, const Value& v2) {
    if (v1.type() != v2.type()) {
        throw CablinRuntimeException("Value::operator-: type of v1 and v2 not equal");
    }

    switch (v1.type()) {
    case ValueType::FLOAT:
        return v1.as<float>() - v2.as<float>();
    case ValueType::INT:
        return v1.as<int>() - v2.as<int>();
    case ValueType::INT64:
        return v1.as<int64_t>() - v2.as<int64_t>();
    default:
        throw CablinRuntimeException("Value::operator-: type of v1 and v2 cannot apply -");
    }
}

inline Value operator*(const Value& v1, const Value& v2) {
    if (v1.type() != v2.type()) {
        throw CablinRuntimeException("Value::operator*: type of v1 and v2 not equal");
    }

    switch (v1.type()) {
    case ValueType::FLOAT:
        return v1.as<float>() * v2.as<float>();
    case ValueType::INT:
        return v1.as<int>() * v2.as<int>();
    case ValueType::INT64:
        return v1.as<int64_t>() * v2.as<int64_t>();
    default:
        throw CablinRuntimeException("Value::operator*: type of v1 and v2 cannot apply *");
    }
}

inline Value operator/(const Value& v1, const Value& v2) {
    if (v1.type() != v2.type()) {
        throw CablinRuntimeException("Value::operator/: type of v1 and v2 not equal");
    }

    switch (v1.type()) {
    case ValueType::FLOAT:
        if (v2.as<float>() == 0) {
            // TODO: check eps?
            throw CablinRuntimeException("Value::operator/: zero division");
        }
        return v1.as<float>() / v2.as<float>();
    case ValueType::INT:
        if (v2.as<int>() == 0) {
            throw CablinRuntimeException("Value::operator/: zero division");
        }
        return v1.as<int>() / v2.as<int>();
    case ValueType::INT64:
        if (v2.as<int64_t>() == 0) {
            throw CablinRuntimeException("Value::operator/: zero division");
        }
        return v1.as<int64_t>() / v2.as<int64_t>();
    default:
        throw CablinRuntimeException("Value::operator/: type of v1 and v2 cannot apply *");
    }
}

inline Value operator>(const Value& v1, const Value& v2) {
    if (v1.type() != v2.type()) {
        throw CablinRuntimeException("Value::operator>: type of v1 and v2 not equal");
    }

    switch (v1.type()) {
    case ValueType::FLOAT:
        return v1.as<float>() > v2.as<float>();
    case ValueType::INT:
        return v1.as<int>() > v2.as<int>();
    case ValueType::INT64:
        return v1.as<int64_t>() > v2.as<int64_t>();
    case ValueType::STRING:
        return v1.as<std::string>() > v2.as<std::string>();
    default:
        throw CablinRuntimeException("Value::operator>: type of v1 and v2 cannot compare");
    }
}

inline Value operator<(const Value& v1, const Value& v2) {
    return v2 > v1;
}

inline Value operator>=(const Value& v1, const Value& v2) {
    return !(v2 < v1).as<bool>();
}

inline Value operator<=(const Value& v1, const Value& v2) {
    return !(v1 > v2).as<bool>();
}

inline Value operator==(const Value& v1, const Value& v2) noexcept {
    if (v1.type() != v2.type()) {
        return false;
    }

    switch (v1.type()) {
    case ValueType::NONE:
        return true;
    case ValueType::BOOL:
        return v1.as<bool>() == v2.as<bool>();
    case ValueType::INT:
        return v1.as<int>() == v2.as<int>();
    case ValueType::INT64:
        return v1.as<int64_t>() == v2.as<int64_t>();
    case ValueType::FLOAT:
        return v1.as<float>() == v2.as<float>();
    case ValueType::STRING:
        return v1.as<std::string>() == v2.as<std::string>();
    }

    return false;
}

inline Value operator%(const Value& v1, const Value& v2) {
    if (v1.type() != v2.type()) {
        throw CablinRuntimeException("Value::operator%: type of v1 and v2 not equal");
    }

    switch (v1.type()) {
    case ValueType::INT:
        if (v2.as<int>() == 0) {
            throw CablinRuntimeException("Value::operator%: zero division");
        }
        return v1.as<int>() % v2.as<int>();
    case ValueType::INT64:
        if (v2.as<int64_t>() == 0) {
            throw CablinRuntimeException("Value::operator%: zero division");
        }
        return v1.as<int64_t>() % v2.as<int64_t>();
    default:
        throw CablinRuntimeException("Value::operator%: type of v1 and v2 cannot apply %");
    }
}

inline Value operator&&(const Value& v1, const Value& v2) {
    return v1.as<bool>() && v2.as<bool>();
}

inline Value operator||(const Value& v1, const Value& v2) {
    return v1.as<bool>() || v2.as<bool>();
}

inline Value operator!(const Value& v1) {
    return !v1.as<bool>();
}


}  // namespace core
}  // namespace cablin
}  // namespace mukyu