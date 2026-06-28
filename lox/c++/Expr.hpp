#include <memory>

#include "Token.hpp"

namespace com::craftinginterpreters::lox {

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
            virtual void accept(Visitor& visitor) const = 0;     
    };  
    
    class BinaryExpr : public Expr {
        std::unique_ptr<Expr> left;
        Token op;
        std::unique_ptr<Expr> right;

        BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
            : left(std::move(left)), op(op), right(std::move(right)) {} 

        void accept(Visitor& visitor) const override {
            visitor.visitBinaryExpr(*this);
        }
    };

    class GroupingExpr : public Expr {
        std::unique_ptr<Expr> expr;

        GroupingExpr(std::unique_ptr<Expr> expr)
            : expr(std::move(expr)) {};

        void accept(Visitor& visitor) const override {
            visitor.visitGroupingExpr(*this);
        }
    };

    class LiteralExpr : public Expr {
        Literal value;

        LiteralExpr(Literal value)
            : value(std::move(value)) {};

        void accept(Visitor& visitor) const override {
            visitor.visitLiteralExpr(*this);
        }
    };

    class UnaryExpr : public Expr {
        Token op;
        std::unique_ptr<Expr> right;

        UnaryExpr(Token op, std::unique_ptr<Expr> right) 
            : op(op), right(std::move(right)) {};

        void accept(Visitor& visitor) const override {
            visitor.visitUnaryExpr(*this);
        }
    };
}
