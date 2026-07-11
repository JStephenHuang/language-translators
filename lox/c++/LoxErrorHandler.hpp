#ifndef LOX_ERROR_HANDLER_HPP
#define LOX_ERROR_HANDLER_HPP

#include <iostream>
#include <string>

#include "Token.hpp"

namespace LoxErrorHandler {
    inline bool had_error = false;
    
    static void report(int line, const std::string& where, const std::string& message) {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
        had_error = true;
    }

    static void error(int line, const std::string& message) {
        report(line, "", message);
    }

    static void error(const Token& token, const std::string& message) {
        if (token.type == END_OF_FILE) {
            report(token.line, " at end", message);
        } else {
            report(token.line, " at '" + token.lexeme + "'", message);
        }
    }

};

#endif
