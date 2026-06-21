#include "Token.hpp"

namespace com::craftinginterpreters::lox {
    Token::Token(const TokenType type, const std::string lexeme, const int line) : type(type), lexeme(lexeme), line(line) {};

    std::ostream& operator<<(std::ostream& os, const Token& token) {
        return os << static_cast<int>(token.type) << " " << token.lexeme;
    }
}


