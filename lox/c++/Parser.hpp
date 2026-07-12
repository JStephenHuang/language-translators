#ifndef PARSER_HPP
#define PARSER_HPP

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Expr.hpp"
#include "Token.hpp"
#include "lox_errors.hpp"


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
    bool is_at_end();

    Token advance();
    Token peek();
    Token previous();

    Token consume(TokenType type, const std::string& message);

    lox::errors::ParseError error(const Token& token, const std::string& message);
    
    void synchronize();


    public:
        Parser(const std::vector<Token>& tokens);

        std::unique_ptr<Expr> parse();

            
};

#endif
