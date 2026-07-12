#include "Parser.hpp"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {};

std::unique_ptr<Expr> Parser::expression() { return equality(); }

std::unique_ptr<Expr> Parser::equality() { 
    std::unique_ptr<Expr> expr = comparison();

    while (match({ BANG_EQUAL, EQUAL_EQUAL })) {
        Token op = previous();
        std::unique_ptr<Expr> right = comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison() {
    std::unique_ptr<Expr> expr = term();

    while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
        Token op = previous();
        std::unique_ptr<Expr> right = term();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term() {
    std::unique_ptr<Expr> expr = factor();

    while (match({ MINUS, PLUS })) {
        Token op = previous();
        std::unique_ptr<Expr> right = factor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor() {
    std::unique_ptr<Expr> expr = unary();

    while (match({ SLASH, STAR })) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary() {
    if (match({ BANG, MINUS })) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({ FALSE })) { return std::make_unique<LiteralExpr>(previous().literal); }
    if (match({ TRUE })) { return std::make_unique<LiteralExpr>(previous().literal); }
    if (match({ NIL })) { return std::make_unique<LiteralExpr>(previous().literal); }

    if (match({ NUMBER, STRING })) {
        return std::make_unique<LiteralExpr>(previous().literal);
    }

    if (match({ LEFT_PAREN })) {
        std::unique_ptr<Expr> expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression");           
        return std::make_unique<GroupingExpr>(std::move(expr));
    }

    throw error(peek(), "Expected expression.");
}

bool Parser::match(const std::initializer_list<TokenType>& types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}   

bool Parser::is_at_end() {
    return peek().type == END_OF_FILE;
}

bool Parser::check(TokenType type) {
    if (is_at_end()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!is_at_end()) current ++;
    return previous();
}

Token Parser::peek() {
    return tokens.at(current);
}

Token Parser::previous() {
    return tokens.at(current - 1);
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw error(peek(), message);
}

void Parser::synchronize() {
    advance();

    while (!is_at_end()) {
        if (previous().type == SEMICOLON) return;

        switch(peek().type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;

        }

        advance();
    }
}

lox::errors::ParseError Parser::error(const Token& token, const std::string& message) {
    lox::errors::error(token, message);
    return lox::errors::ParseError(message);
}

std::unique_ptr<Expr> Parser::parse() {
    try {
        return expression();
    } catch (const lox::errors::ParseError& error) {
        return nullptr;
    }
}
