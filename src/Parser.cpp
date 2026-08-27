#include "Parser.hpp"

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

const TOken& Parser::advance(){
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