#ifndef PARSER_HPP
#define PARSER_HPP

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "LoxErrorHandler.hpp"
#include "Expr.hpp"
#include "Token.hpp"

class ParseError : public std::runtime_error {
    public:
        explicit ParseError(const std::string& message) : std::runtime_error(message) {}
}; 
class Parser {
    std::vector<Token> tokens;
    int current = 0;

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    bool match(const std::initializer_list<TokenType>& types);
    bool check(TokenType type);
    bool isAtEnd();

    Token advance();
    Token peek();
    Token previous();

    Token consume(TokenType type, const std::string& message);

    ParseError error(const Token& token, const std::string& message);
    
    void synchronize();


    public:
        Parser(const std::vector<Token>& tokens);

        std::unique_ptr<Expr> parse();

            
};

#endif
