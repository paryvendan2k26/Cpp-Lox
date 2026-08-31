#pragma once

#include <memory>
#include <vector>

#include "Token.hpp"
#include "Expr.hpp"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);

    std::unique_ptr<Expr> parse();

private:
    
    class ParseError {};

    const std::vector<Token>& tokens;
    int current = 0;

    const Token& peek();
    const Token& previous();
    const Token& advance();
    bool check(TokenType type);
    bool match(TokenType type);

    bool isAtEnd();

    std::unique_ptr<Expr> primary();
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> unary();

    Token consume(TokenType type, const std::string& message);

    ParseError error(const Token& token, const std::string& message);
};  


