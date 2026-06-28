#include "Scanner.hpp"
#include <string>

namespace com::craftinginterpreters::lox {
    bool Scanner::is_at_end() const {
        return current >= source.length();
    }

    bool Scanner::is_digit(char c) const {
        return c >= '0' && c <= '9';
    }
    
    bool Scanner::is_alpha(char c) const {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }
    
    bool Scanner::is_alphanumeric(char c) const {
        return is_digit(c) || is_alpha(c); 
    }

    char Scanner::advance() {
        return source[current++];

    }

    char Scanner::peek() const {
        if (is_at_end()) return '\0';
        return source[current];
    }

    char Scanner::peekNext() const {
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    bool Scanner::match(char expected) {
        if (is_at_end() || source[current] != expected) return false;

        current++;
        return true;
    }

    void Scanner::add_token(TokenType type) {
        add_token(type, Literal()); 
    }

    void Scanner::add_token(TokenType type, const Literal& literal) {
        std::string text = source.substr(start, current-start);
        tokens.push_back(Token(type, text, literal, line));
    }

    void Scanner::string() {
        while (peek() != '"' && !is_at_end()) {
            if (peek() == '\n') line ++;
            advance();
        }

        if (is_at_end()) {
            add_token(ERROR_STRING);
            return;
        }

        // consume ending quotes
        advance();

        Literal literal;
        literal.str = source.substr(start + 1, current-start - 1);

        add_token(STRING, literal);
    }

    void Scanner::number() {
        while (is_digit(peek())) advance();

        // if we encounter a fractional part
        if (peek() == '.' && is_digit(peekNext())) {

            // consume the "."
            advance();
            while (is_digit(peek())) advance();
        }

        Literal literal;
        literal.num = std::stod(source.substr(start, current-start));
        add_token(NUMBER, literal);
    }

    void Scanner::identifier() {
        while (is_alphanumeric(peek())) advance();

        std::string text = source.substr(start, current-start);
        auto it = keywords.find(text);
        
        TokenType type = it == keywords.end() ? IDENTIFIER : it->second;
        Literal literal;

        if (type == TRUE) {
            literal.boolean = true;
        } else if (type == FALSE) {
            literal.boolean = false;
        }

        add_token(type, literal);
    }
    
    void Scanner::scan_token() {
        char c = advance();
        switch (c) {
            case '(': add_token(LEFT_PAREN); break;
            case ')': add_token(RIGHT_PAREN); break;
            case '{': add_token(LEFT_BRACE); break;
            case '}': add_token(RIGHT_BRACE); break;
            case ',': add_token(COMMA); break;
            case '.': add_token(DOT); break;
            case '-': add_token(MINUS); break;
            case '+': add_token(PLUS); break;
            case ';': add_token(SEMICOLON); break;
            case '*': add_token(STAR); break;

            case '!': add_token(match('=') ? BANG_EQUAL : BANG); break;
            case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
            case '<': add_token(match('=') ? LESS_EQUAL : LESS); break;
            case '>': add_token(match('=') ? GREATER_EQUAL : GREATER); break;

            case '/':
                if (match('/')) {
                    // double slash comments
                    while (peek() != '\n' && !is_at_end()) advance();
                } else if (match('*')) {
                    // c style block comments
                    // while we don't reach the end or encounter the closing */
                    // keep ignoring characters
                    while ((peek() != '*' || peekNext() != '/') && !is_at_end()) {
                        if (peek() == '\n') line++;
                        advance();
                    }

                    if (is_at_end()) {
                        add_token(ERROR_BLOCK_COMMENT);
                        return;
                    }
                    // consume the * and the /
                    advance();
                    advance();
                } else {
                    add_token(SLASH);
                }
                break;


            // ignore whitespace.
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
                line++;
                break;
                
            case '"': string(); break;
            
            default:
                if (is_digit(c)) {
                    number();
                } else if (is_alpha(c)) {
                    identifier();
                } else {
                    add_token(UNKNOWN_TOKEN);
                }
                
                break;
        }
    }
    Scanner::Scanner(const std::string& source) : source(source) {};

    std::vector<Token> Scanner::scan_tokens() {
        while (!is_at_end()) {
            start = current;
            scan_token();
        }
        tokens.push_back(Token(END_OF_FILE, "", Literal(), line));
        return tokens;
    };

}
