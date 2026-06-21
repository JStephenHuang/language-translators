#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <ostream>
#include <string>

namespace com::craftinginterpreters::lox {
    enum TokenType {
        // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // One or two character tokens.
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals.
        IDENTIFIER, STRING, NUMBER,

        // Keywords.
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

        UNKNOWN_TOKEN, ERROR_STRING, ERROR_BLOCK_COMMENT,
        END_OF_FILE
        // EOF (already a pre built cpp enum)
    };

    class Token {
        public:
        TokenType type;
        std::string lexeme;
        int line;

        
        Token(const TokenType type, const std::string lexeme, const int line);
        friend std::ostream& operator<<(std::ostream& os, const Token& token); 
    };

    /* 
    I could do:

    struct Token {
        TokenType type;
        std::string lexeme;
        int line;
    }

    but I guess that wouldn't be much different from c. we take advantage of the c++ class haha.
    */
}

#endif