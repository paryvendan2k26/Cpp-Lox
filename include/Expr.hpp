#pragma once

#include "Token.hpp"

#include <memory>
#include <string>
#include <variant>
#include <utility>

class Expr {
public:
    virtual ~Expr() = default;
};

class Binary: public Exper{
    public:
    Binary(
        std::unique_ptr<Expr> left,
        Token operatorToken,
        std::unique_ptr<Expr> right
    )
    : left(left),
    operatorToken(operatorToken),
    right(right){

    }

        std::unique_ptr<Expr> left;
        Token operatorToken;
        std::unique_ptr<Expr> right;


};

class Grouping : public Expr {
public:
    Grouping(std::unique_ptr<Expr> expression)
        : expression(expression) {}

    std::unique_ptr<Expr> expression;
};

class Literal : public Expr {
public:
    Literal(LiteralValue value)
        : value(std::move(value)) {
    }

    LiteralValue value;
};

class Unary : public Expr {
public:
    Unary(Token operatorToken, std::unique_ptr<Expr> right)
        : operatorToken(operatorToken),
          right(right) {}

    Token operatorToken;
    std::unique_ptr<Expr> right;
};