#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Scanner.hpp"
#include "Token.hpp"

class Lox {
    inline static bool had_error = false;

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

        if (had_error) std::exit(65);
    }

    void run_prompt() {
        std::string line;
        for (;;) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) break;
            run(line);
            had_error = false;
        }
    }

    void run(const std::string& source) {
        Scanner scanner = Scanner(source);
        std::vector<Token> tokens = scanner.scan_tokens();

        for (const Token& token : tokens) {
            if (token.type == UNKNOWN_TOKEN) {
                error(token.line, "Unexpected character: " + token.lexeme);
                continue;
            }
            if (token.type == ERROR_STRING) {
                error(token.line, "Unexpected string: " + token.lexeme);
                continue;
            }
            if (token.type == ERROR_BLOCK_COMMENT) {
                error(token.line, "Unexpected block comment: " + token.lexeme);
                continue;
            }
            std::cout << token << " "  << "\n";

        }

    }

    static void error(int line, const std::string& message) {
        report(line, "", message);
    }

    static void report(int line, const std::string& where, const std::string& message) {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
        had_error = true;
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

