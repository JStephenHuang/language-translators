#pragma once

#include <stack>

#include "Expr.hpp"
#include "lox_errors.hpp"

class Interpreter : public Visitor {

    void evaluate(Expr& expr);

    bool is_truthy(const lox_literal& literal) const;
    // bool is_equal(const lox_literal& a, const lox_literal& b) const;

    void check_number_operand(const Token& op, const lox_literal& operand) const;
    void check_number_operands(const Token& op, const lox_literal& left, const lox_literal& right) const;

    lox_literal pop();

    public:

        // results stack, holds intermediate values as ast nodes resolve
        std::stack<lox_literal> rs;

        Interpreter() = default;
        ~Interpreter() = default;

        void visit_binary_expr(BinaryExpr& expr) override;
        void visit_grouping_expr(GroupingExpr& expr) override;
        void visit_literal_expr(LiteralExpr& expr) override;
        void visit_unary_expr(UnaryExpr& expr) override;

        void interpret(Expr& expression);
};