#include "Interpreter.hpp"

void Interpreter::evaluate(Expr& expr) {
    expr.accept(*this);
}

bool Interpreter::is_truthy(const lox_literal& literal) const {
    if (is_nil(literal)) {
        return false;
    }

    if (is_bool(literal)) {
        return std::get<bool>(literal);
    }

    return false;
}

void Interpreter::check_number_operand(const Token& token, const lox_literal& operand) const {
    if (is_number(operand)) return;
    throw lox::errors::RuntimeError(token, "Operand must be a number.");
}

void Interpreter::check_number_operands(const Token& op, const lox_literal& left, const lox_literal& right) const {
    if (is_number(left) && is_number(right)) return;

    throw lox::errors::RuntimeError(op, "Operands must be a numbers.");
}


void Interpreter::visit_literal_expr(LiteralExpr& expr) {
    rs.push(expr.value);
}

void Interpreter::visit_grouping_expr(GroupingExpr& expr) {
    evaluate(*expr.expr);
}

void Interpreter::visit_unary_expr(UnaryExpr& expr) {
    evaluate(*expr.right);

    switch (expr.op.type) {
        case BANG: {
            bool value = !is_truthy(pop());
            rs.push(value);

            return;
        }
        case MINUS: {
            lox_literal right = rs.top();

            check_number_operand(expr.op, right);

            double value = -std::get<double>(right);

            rs.pop();
            rs.push(value);

            return;
        }
        default:
            // unreachable
            return;
    }
}

void Interpreter::visit_binary_expr(BinaryExpr& expr) {
    evaluate(*expr.left);
    evaluate(*expr.right);

    lox_literal right = rs.top();
    rs.pop();

    lox_literal left = rs.top();
    rs.pop();

    switch(expr.op.type) {

        case GREATER: {
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) > std::get<double>(right));
            return;
        }

        case GREATER_EQUAL: {
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) >= std::get<double>(right));
            return;
        }
        case LESS: {
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) < std::get<double>(right));
            return;
        }

        case LESS_EQUAL: {
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) <= std::get<double>(right));
            return;
        }

        case BANG_EQUAL: {
            rs.push(!(left == right));
            return;
        }

        case EQUAL_EQUAL: {
            rs.push(left == right);
            return;
        }

        case MINUS: {
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) - std::get<double>(right));
            return;
        }

        case PLUS: {
            if (is_number(left) && is_number(right)) {
                rs.push(std::get<double>(left) + std::get<double>(right));
                return;
            }

            if (is_string(left) && is_string(right)) {
                rs.push(std::get<std::string>(left) + std::get<std::string>(right));
                return;
            }

            throw lox::errors::RuntimeError(expr.op, "Operands must be two numbers or two strings.");
        }

        case SLASH: { 
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) / std::get<double>(right));
            return;
        }

        case STAR: {
            check_number_operands(expr.op, left, right);
            rs.push(std::get<double>(left) * std::get<double>(right));
            return;
        }

        default:
            // unreachable
            return;
    }
}

void Interpreter::interpret(Expr& expr) {
    try {
        evaluate(expr);

        // check if empty?

        lox_literal value = rs.top();
        rs.pop();

        std::cout << value << "\n";
    } catch (const lox::errors::RuntimeError& error) {
        lox::errors::runtime_error(error);
    }
}

// rs helper

lox_literal Interpreter::pop() {
    // pops the value for us
    lox_literal l = rs.top();
    rs.pop();
    return l;
}