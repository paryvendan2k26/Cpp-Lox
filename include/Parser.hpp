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
    const std::vector<Token>& tokens;
    int current = 0;

       const Token& peek();
    const Token& previous();
    const Token& advance();
    bool check(TokenType type);
    bool match(TokenType type);

    bool isAtEnd();
};