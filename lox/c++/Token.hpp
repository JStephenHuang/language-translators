#pragma once

#include <ostream>
#include <string>
#include <string_view>
#include <variant>

#include "lox_literal.hpp"

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

    END_OF_FILE
        // EOF (already a pre built cpp enum)
};

std::string_view to_string(TokenType type);

class Token {
    public:
        TokenType type;
        std::string lexeme;
        lox_literal literal;
        int line;

        Token(const TokenType type, const std::string lexeme, lox_literal l, const int line);
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
