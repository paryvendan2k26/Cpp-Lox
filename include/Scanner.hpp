#pragma once

#include <string>
#include <vector>

#include "Token.hpp"

using namespace std;

class Scanner {
public:
    Scanner(string source);

    vector<Token> scanTokens();

private:
    string source;
    vector<Token> tokens;

    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();
    bool match(char expected);


    void scanToken();
    void addToken(TokenType type);

    void scanString();
    void scanNumber();

    bool isAlpha(char c);
    bool isAlphaNumeric(char c);

    void scanIdentifier();
    TokenType identifierType(const string& text);
    
};