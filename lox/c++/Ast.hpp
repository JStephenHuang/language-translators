#pragma once

#include <memory>

#include "Token.hpp"

class BinaryExpr;
class GroupingExpr;
class LiteralExpr;
class UnaryExpr;

class ExpressionStmt;
class PrintStmt;

class Visitor {
    public:
        virtual void visit_binary_expr(BinaryExpr& expr) = 0;
        virtual void visit_grouping_expr(GroupingExpr& expr) = 0;
        virtual void visit_literal_expr(LiteralExpr& expr) = 0;
        virtual void visit_unary_expr(UnaryExpr& expr) = 0;

        virtual void visit_expression_stmt(ExpressionStmt& stmt) = 0;
        virtual void visit_print_stmt(PrintStmt& stmt) = 0;
};

class Expr {
    public:
        virtual ~Expr() = default;
        virtual void accept(Visitor& visitor) = 0;     
};  

class BinaryExpr : public Expr {
    public:
        std::unique_ptr<Expr> left;
        Token op;
        std::unique_ptr<Expr> right;

        BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
            : left(std::move(left)), op(op), right(std::move(right)) {} 

        void accept(Visitor& visitor) override {
            visitor.visit_binary_expr(*this);
        }
};

class GroupingExpr : public Expr {
    public:
        std::unique_ptr<Expr> expr;

        GroupingExpr(std::unique_ptr<Expr> expr)
            : expr(std::move(expr)) {};

        void accept(Visitor& visitor) override {
            visitor.visit_grouping_expr(*this);
        }
};

class LiteralExpr : public Expr {
    public:
        lox_literal value;

        LiteralExpr(lox_literal value)
            : value(std::move(value)) {};

        void accept(Visitor& visitor) override {
            visitor.visit_literal_expr(*this);
        }
};

class UnaryExpr : public Expr {
    public:
        Token op;
        std::unique_ptr<Expr> right;

        UnaryExpr(Token op, std::unique_ptr<Expr> right) 
            : op(op), right(std::move(right)) {};

        void accept(Visitor& visitor) override {
            visitor.visit_unary_expr(*this);
        }
};

class Stmt {
    public:
        virtual ~Stmt() = default;
        virtual void accept(Visitor& visitor) = 0;
};

class ExpressionStmt : public Stmt {
    public: 
        std::unique_ptr<Expr> expr;

        ExpressionStmt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {};

        void accept(Visitor& visitor) override {
            visitor.visit_expression_stmt(*this);
        }
};

class PrintStmt : public Stmt {
    public: 
        std::unique_ptr<Expr> expr;

        PrintStmt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {};

        void accept(Visitor& visitor) override {
            visitor.visit_print_stmt(*this);
        }
};