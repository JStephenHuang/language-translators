#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include <initializer_list>
#include <iostream>
#include <memory>

#include "Expr.hpp"
#include "Token.hpp"

class AstPrinter : public Visitor {
    void parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);

    public:
        AstPrinter() {};

        void print(Expr& expr);

        void visit_binary_expr(BinaryExpr& expr) override;
        void visit_grouping_expr(GroupingExpr& expr) override;
        void visit_literal_expr(LiteralExpr& expr) override;
        void visit_unary_expr(UnaryExpr& expr) override;

};

#endif
