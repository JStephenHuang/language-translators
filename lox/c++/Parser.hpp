#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Ast.hpp"
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

    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> expression_stmt();
    std::unique_ptr<Stmt> print_stmt();
    

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

        std::vector<std::unique_ptr<Stmt>> parse();

            
};
