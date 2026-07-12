#include "AstPrinter.hpp"

void AstPrinter::parenthesize(const std::string& name, std::initializer_list<Expr*> exprs) {

        std::cout << "(" << name; 

        for (Expr* expr : exprs) {
            std::cout << " ";
            expr->accept(*this);
        }        
        std::cout << ")";
    }

void AstPrinter::print(Expr& expr) {
    expr.accept(*this);
}

void AstPrinter::visit_binary_expr(BinaryExpr& expr) {
    parenthesize(expr.op.lexeme, { expr.left.get(), expr.right.get() }); 
}

void AstPrinter::visit_grouping_expr(GroupingExpr& expr) {
    parenthesize("group", { expr.expr.get() });
}

void AstPrinter::visit_literal_expr(LiteralExpr& expr) {
    std::cout << expr.value; 
}

void AstPrinter::visit_unary_expr(UnaryExpr& expr) {
    parenthesize(expr.op.lexeme, { expr.right.get() });
}