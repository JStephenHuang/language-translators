#pragma once

#include <stdexcept>
#include <string_view>

#include "Token.hpp"

namespace lox::errors {
    class ParseError : public std::runtime_error {
        public:
            explicit ParseError(std::string_view message);
    };

    class RuntimeError : public std::runtime_error {
        public:
            Token t;
            explicit RuntimeError(Token t, std::string_view message);
    };
    
    extern bool had_error;
    extern bool had_runtime_error;

    void report(int line, std::string_view where, std::string_view message);
    void error(int line, std::string_view message);
    void error(const Token& token, std::string_view message);
    void runtime_error(const RuntimeError& error);

}