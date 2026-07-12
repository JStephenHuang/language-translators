#pragma once

#include <variant>
#include <iostream>
#include <type_traits>
#include <string>

using lox_literal = std::variant<std::monostate, double, bool, std::string>;

inline std::ostream& operator<<(std::ostream& os, const lox_literal& value) {
    std::visit([&os](const auto& v) {
        using raw = std::decay_t<decltype(v)>;

        // if value is monostate
        if constexpr (std::is_same_v<raw, std::monostate>) {
            os << "nil";
        // if value is bool
        } else if constexpr (std::is_same_v<raw, bool>) {
            os << (v ? "true" : "false");
        // if string or double (already has << support)
        } else {
            os << v;
        }
    }, value);

    return os;
}

inline bool is_nil(const lox_literal& l) {
    return std::holds_alternative<std::monostate>(l);
}

inline bool is_bool(const lox_literal& l) {
    return std::holds_alternative<bool>(l);
}

inline bool is_number(const lox_literal& l) {
    return std::holds_alternative<double>(l);
}

inline bool is_string(const lox_literal& l) {
    return std::holds_alternative<std::string>(l);
}