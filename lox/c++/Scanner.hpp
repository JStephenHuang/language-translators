#include <string>
#include <vector>
#include <unordered_map>

#include "Token.hpp"

namespace com::craftinginterpreters::lox {
    class Scanner {
        std::string source;
        std::vector<Token> tokens;
        int start = 0, current = 0, line = 1;

        inline static const std::unordered_map<std::string, TokenType> keywords = {
            {"and",    TokenType::AND},
            {"class",  TokenType::CLASS},
            {"else",   TokenType::ELSE},
            {"false",  TokenType::FALSE},
            {"for",    TokenType::FOR},
            {"fun",    TokenType::FUN},
            {"if",     TokenType::IF},
            {"nil",    TokenType::NIL},
            {"or",     TokenType::OR},
            {"print",  TokenType::PRINT},
            {"return", TokenType::RETURN},
            {"super",  TokenType::SUPER},
            {"this",   TokenType::THIS},
            {"true",   TokenType::TRUE},
            {"var",    TokenType::VAR},
            {"while",  TokenType::WHILE},
        };

        bool is_at_end() const;
        bool is_digit(char c) const;
        bool is_alpha(char c) const;
        bool is_alphanumeric(char c) const;
        
        char advance();
        char peek() const;
        char peekNext() const;
        bool match(char expected);

        void add_token(TokenType type);
        void scan_token();

        void string();
        void number();
        void identifier();

        public:
        Scanner(const std::string& source);
        std::vector<Token> scan_tokens();

    };
}