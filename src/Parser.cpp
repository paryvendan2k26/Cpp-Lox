#include "Parser.hpp"
#include "Lox.hpp"

Parser::Parser(const std::vector<Token>& tokens)
    :tokens(tokens){

    }

std::unique_ptr<Expr> Parser::parse() {
    return nullptr;
}

const Token& Parser::peek(){
    return tokens[current];
}

const Token& Parser::previous(){
    return tokens[current-1];
}

const Token& Parser::advance(){
    if(!isAtEnd()){
        current++;
    }
    return previous();
}

bool Parser::isAtEnd(){
    return peek().type==TokenType::END_OF_FILE;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) {
        return false;
    }

    return peek().type == type;
}

bool Parser::match(TokenType type) {
    if (!check(type)) {
        return false;
    }

    advance();
    return true;
}

std::unique_ptr<Expr> Parser::primary(){
    if(match(TokenType::FALSE)){
        return std::make_unique<Literal>(false);
    }

    if (match(TokenType::TRUE)) {
        return std::make_unique<Literal>(true);
    }

    if (match(TokenType::NIL)) {
        return std::make_unique<Literal>(nullptr);
    }

    if (match(TokenType::NUMBER)) {
        return std::make_unique<Literal>(previous().literal);
    }

    if (match(TokenType::STRING)) {
        return std::make_unique<Literal>(previous().literal);
    }

    return nullptr;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return advance();
    }

    throw error(peek(), message);
}


Parser::ParseError Parser::error(
    const Token& token,
    const std::string& message
) {
    Lox::error(token.line, message);
    return ParseError();
}

std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

std::unique_ptr<Expr> Parser::equality() {

    auto expr = comparison();

    while (
        match(TokenType::BANG_EQUAL) ||
        match(TokenType::EQUAL_EQUAL)
    ) {
        Token operatorToken = previous();

        auto right = comparison();

        expr = std::make_unique<Binary>(
            std::move(expr),
            operatorToken,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary() {
    if (match(TokenType::BANG) || match(TokenType::MINUS)) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();

        return std::make_unique<Unary>(
            op,
            std::move(right)
        );
    }

    return primary();
}

std::unique_ptr<Expr> Parser::factor() {
    std::unique_ptr<Expr> expr = unary();

    while (match(TokenType::SLASH) || match(TokenType::STAR)) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();

        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison() {
    auto expr = term();

    while (
        match(TokenType::GREATER) ||
        match(TokenType::GREATER_EQUAL) ||
        match(TokenType::LESS) ||
        match(TokenType::LESS_EQUAL)
    ) {
        Token op = previous();
        auto right = term();

        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term() {
    auto expr = factor();

    while (
        match(TokenType::MINUS) ||
        match(TokenType::PLUS)
    ) {
        Token op = previous();
        auto right = factor();

        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    return expr;
}