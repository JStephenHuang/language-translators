#include <iostream>
#include <vector>

#include "Token.hpp"

namespace com::craftinginterpreters::lox {
    class Parser {
        std::vector<Token> tokens;
        int current = 0;

        public:
        Parser(const std::vector<Token>& tokens) : tokens(tokens) {};
    };
}
