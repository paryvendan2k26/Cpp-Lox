#pragma once

#include <memory>
#include <string>
#include <utility>
#include <variant>

#include "Token.hpp"


using LiteralValue = std::variant<
    std::nullptr_t,
    bool,
    double,
    std::string
>;


class Expr {
public:
    virtual ~Expr() = default;
};


class Binary : public Expr {
public:
    Binary(
        std::unique_ptr<Expr> left,
        Token operatorToken,
        std::unique_ptr<Expr> right
    )
        : left(std::move(left)),
          operatorToken(std::move(operatorToken)),
          right(std::move(right)) {
    }

    std::unique_ptr<Expr> left;
    Token operatorToken;
    std::unique_ptr<Expr> right;
};


class Grouping : public Expr {
public:
    Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {
    }

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
    Unary(
        Token operatorToken,
        std::unique_ptr<Expr> right
    )
        : operatorToken(std::move(operatorToken)),
          right(std::move(right)) {
    }

    Token operatorToken;
    std::unique_ptr<Expr> right;
};