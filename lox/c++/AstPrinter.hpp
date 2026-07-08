#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include <initializer_list>
#include <iostream>
#include <memory>

#include "Expr.hpp"
#include "Token.hpp"

using namespace std;

class AstPrinter : public Visitor {
    void parenthesize(const std::string& name, std::initializer_list<const Expr*> exprs) const {

        cout << "(" << name; 

        for (const Expr* expr : exprs) {
            cout << " ";
            expr->accept(*this);
        }        
        cout << ")";
    }
    public:
        AstPrinter() {};

        void print(const Expr& expr) {
           expr.accept(*this);
        }

        void visitBinaryExpr(const BinaryExpr& expr) const {
            parenthesize(expr.op.lexeme, { expr.left.get(), expr.right.get() }); 
        }

        void visitGroupingExpr(const GroupingExpr& expr) const {
            parenthesize("group", { expr.expr.get() });
        }
        
        void visitLiteralExpr(const LiteralExpr& expr) const {
            cout << expr.t.lexeme; 
        }

        void visitUnaryExpr(const UnaryExpr& expr) const {
            parenthesize(expr.op.lexeme, { expr.right.get() });
        }
};

#endif
