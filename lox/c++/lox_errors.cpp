#include "lox_errors.hpp"

namespace lox::errors {

    ParseError::ParseError(std::string_view message)
        : std::runtime_error(std::string(message)) {}

    RuntimeError::RuntimeError(Token t, std::string_view message) 
        : std::runtime_error(std::string(message)), t(t) {}

    bool had_error = false;
    bool had_runtime_error = false;

    void report(int line, std::string_view where, std::string_view message) {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << '\n';

        had_error = true;
    }

    void error(int line, std::string_view message) {
        report(line, "", message);
    }

    void error(const Token& token, std::string_view message) {
        if (token.type == END_OF_FILE) {
            report(token.line, " at end", message);
        } else {
            report(token.line, " at '" + token.lexeme + "'", message);
        }
    }

    void runtime_error(const RuntimeError& error) {
        std::cout << error.what() << " [line " << error.t.line << + "]";
        had_runtime_error = true;
    }

}