#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>

#include "Token.hpp"

class BinaryExpr;
class GroupingExpr;
class LiteralExpr;
class UnaryExpr;

class Visitor {
    public:
        virtual void visitBinaryExpr(const BinaryExpr& expr) const = 0;
        virtual void visitGroupingExpr(const GroupingExpr& expr) const = 0;
        virtual void visitLiteralExpr(const LiteralExpr& expr) const = 0;
        virtual void visitUnaryExpr(const UnaryExpr& expr) const = 0;
};

class Expr {
    public:
        virtual ~Expr() = default;
        virtual void accept(const Visitor& visitor) const = 0;     
};  

class BinaryExpr : public Expr {
    public:
        std::unique_ptr<Expr> left;
        Token op;
        std::unique_ptr<Expr> right;

        BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
            : left(std::move(left)), op(op), right(std::move(right)) {} 

        void accept(const Visitor& visitor) const override {
            visitor.visitBinaryExpr(*this);
        }
};

class GroupingExpr : public Expr {
    public:
        std::unique_ptr<Expr> expr;

        GroupingExpr(std::unique_ptr<Expr> expr)
            : expr(std::move(expr)) {};

        void accept(const Visitor& visitor) const override {
            visitor.visitGroupingExpr(*this);
        }
};

class LiteralExpr : public Expr {
    public:
        Token t;

        LiteralExpr(Token token)
            : t(token) {};

        void accept(const Visitor& visitor) const override {
            visitor.visitLiteralExpr(*this);
        }
};

class UnaryExpr : public Expr {
    public:
        Token op;
        std::unique_ptr<Expr> right;

        UnaryExpr(Token op, std::unique_ptr<Expr> right) 
            : op(op), right(std::move(right)) {};

        void accept(const Visitor& visitor) const override {
            visitor.visitUnaryExpr(*this);
        }
};

#endif
