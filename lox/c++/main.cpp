// #include "AstPrinter.hpp"
#include "Lox.cpp"

int main() {
    Lox lox;
    lox.main({"main.lox"});

    // ast printer test chapter 5
    // Literal number_123{false, 123, ""};
    // Literal number_45_67{false, 45.67, ""};

    // std::unique_ptr<Expr> expression = std::make_unique<BinaryExpr>(
    //     std::make_unique<UnaryExpr>(
    //         Token(MINUS, "-", {}, 1),
    //         std::make_unique<LiteralExpr>(Token(NUMBER, "123", number_123, 1))
    //     ),
    //     Token(STAR, "*", {}, 1),
    //     std::make_unique<GroupingExpr>(
    //         std::make_unique<LiteralExpr>(Token(NUMBER, "45.67", number_45_67, 1))
    //     )
    // );

    // AstPrinter printer;
    // printer.print(*expression);

    return 0;
}
