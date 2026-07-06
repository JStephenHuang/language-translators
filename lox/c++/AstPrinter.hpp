#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include <initializer_list>
#include <iostream>
#include <memory>

#include "Expr.hpp"

namespace com::craftinginterpreters::lox {  
    class AstPrinter : public Visitor {
        void parenthesize(const std::string& name, std::initializer_list<const Expr*> exprs) {

            std::cout << "(" << name; 

            for (const Expr* expr : exprs) {
                std::cout << " ";
                expr->accept(*this);
            }        
            std::cout << ")";
        }
        public:
            void print(const Expr& expr) {
               expr.accept(*this);
            }

            void visitBinaryExpr(const BinaryExpr& expr) {
                parenthesize(expr.op.lexeme, {expr.left.get(), expr.right.get()}); 
            }
    };

}

#endif
