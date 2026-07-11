#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "AstPrinter.hpp"
#include "LoxErrorHandler.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Token.hpp"

class Lox {
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

        if (LoxErrorHandler::had_error) std::exit(65);
    }

    void run_prompt() {
        std::string line;
        for (;;) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) break;
            run(line);
            LoxErrorHandler::had_error = false;
        }
    }

    void run(const std::string& source) {
        Scanner scanner = Scanner(source);
        std::vector<Token> tokens = scanner.scan_tokens();

        Parser parser = Parser(tokens);
        std::unique_ptr<Expr> expression = parser.parse();

        if (LoxErrorHandler::had_error) return;

        AstPrinter().print(*expression);
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

