#include "Token.hpp"

Token::Token(
    TokenType type,
    std::string lexeme,
    std::string literal,
    int line
)
    : type(type),
      lexeme(lexeme),
      literal(literal),
      line(line) {
}

std::string Token::toString() const {
    return lexeme;
}