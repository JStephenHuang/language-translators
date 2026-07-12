#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Token.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

#include "AstPrinter.hpp"
#include "lox_errors.hpp"

class Lox {

    Interpreter interpreter;

    void run_file(const std::string& path) {
        std::ifstream file(path);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + path);
        }

        //std::string line;
        std::stringstream ss;

        ss << file.rdbuf();
        // while (std::getline(file, line)) {
        //    ss << line;
        // }

        run(ss.str());

        if (lox::errors::had_error) std::exit(65);
        if (lox::errors::had_runtime_error) std::exit(70);
    }

    void run_prompt() {
        std::string line;
        for (;;) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) break;
            run(line);
            lox::errors::had_error = false;
        }
    }

    void run(const std::string& source) {
        Scanner scanner = Scanner(source);
        std::vector<Token> tokens = scanner.scan_tokens();

        Parser parser = Parser(tokens);
        std::unique_ptr<Expr> expression = parser.parse();

        if (lox::errors::had_error) return;
        
        AstPrinter().print(*expression);

        std::cout << "\n";

        interpreter.interpret(*expression);

    }

    public:
    void main(const std::vector<std::string>& args) {
        if (args.size() > 1) {
            std::cout << "Usage: jlox [script] \n";
            std::exit(64);
        } else if (args.size() == 1) {
            run_file(args[0]);
        } else {
            run_prompt();
        }
    }
};

