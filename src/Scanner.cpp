#include "Scanner.hpp"
#include "Lox.hpp"
#include <cctype>

using namespace std;

Scanner:: Scanner(string source)
    :source(source){
}

bool Scanner::isAtEnd(){
    return current>=source.length();
}

char Scanner::advance(){
    current++;
    return source[current-1];
}

void Scanner::addToken(TokenType type){
    string text=source.substr(start,current-start);
    tokens.push_back(Token(type,text,"",line));
}

bool Scanner::match(char expected){
    if(isAtEnd()){
        return false; 
    }

    if(source[current]!=expected){
        return false;
    }

    current++;
    return true;
}

char Scanner::peek(){
    if(isAtEnd()){
        return '\0';
    }
    return source[current];
}

void Scanner::scanString(){
    while(peek()!='"'&& !isAtEnd()){
        if(peek()=='\n'){
            line++;
        }

        advance();
    }

    if(isAtEnd()){
        Lox::error(line, "Unterminated string.");
        return;
    }

    advance();

    string value=source.substr(start+1,current-start-2);

    tokens.push_back(Token(TokenType::STRING, source.substr(start, current-start),value,line));
}

void Scanner::scanNumber(){
    while(isdigit(peek())){
        advance();
    }

    if(peek()=='.' && isdigit(peekNext())){
        advance();

        while(isdigit(peek())){
            advance();
        }
    }

    string value=source.substr(start, current-start);

    tokens.push_back(
        Token(
            TokenType::NUMBER,
            value,
            value,
            line
        )
    );
}

char Scanner::peekNext(){
    if(current+1>=source.length()){
        return '\0';
    }

    return source[current+1];
}

bool Scanner::isAlpha(char c){
    return(c>='a' && c<='z')|| (c>='A' && c<='Z')|| c=='_';
}

bool Scanner::isAlphaNumeric(char c) {

    return isAlpha(c) || isdigit(c);
}

void Scanner::scanIdentifier(){
    while(isAlphaNumeric(peek())){
        advance();
    }

    string text=source.substr(
        start, current-start
    );

    TokenType type=identifierType(text);

    addToken(type);
}

TokenType Scanner::identifierType(const string& text) {

    if (text == "and") return TokenType::AND;
    if (text == "class") return TokenType::CLASS;
    if (text == "else") return TokenType::ELSE;
    if (text == "false") return TokenType::FALSE;
    if (text == "for") return TokenType::FOR;
    if (text == "fun") return TokenType::FUN;
    if (text == "if") return TokenType::IF;
    if (text == "nil") return TokenType::NIL;
    if (text == "or") return TokenType::OR;
    if (text == "print") return TokenType::PRINT;
    if (text == "return") return TokenType::RETURN;
    if (text == "super") return TokenType::SUPER;
    if (text == "this") return TokenType::THIS;
    if (text == "true") return TokenType::TRUE;
    if (text == "var") return TokenType::VAR;
    if (text == "while") return TokenType::WHILE;

    return TokenType::IDENTIFIER;
}


void Scanner::scanToken() {

    char c = advance();

    switch (c) {

        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;

        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;

        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;

        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;

        case ',':
            addToken(TokenType::COMMA);
            break;

        case '.':
            addToken(TokenType::DOT);
            break;

        case '-':
            addToken(TokenType::MINUS);
            break;

        case '+':
            addToken(TokenType::PLUS);
            break;

        case ';':
            addToken(TokenType::SEMICOLON);
            break;

        case '*':
            addToken(TokenType::STAR);
            break;

        case '!':
            addToken(
                match('=') 
                    ? TokenType::BANG_EQUAL
                    : TokenType::BANG
            );
            break;

        case '=':
            addToken(
                match('=')
                    ? TokenType::EQUAL_EQUAL
                    : TokenType::EQUAL
            );
            break;

        case '<':
            addToken(
                match('=')
                    ? TokenType::LESS_EQUAL
                    : TokenType::LESS
            );
            break;

        case '>':
            addToken(
                match('=')
                    ? TokenType::GREATER_EQUAL
                    : TokenType::GREATER
            );
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        case '/':
            if(match('/')){
                while (peek() != '\n' && !isAtEnd()) {
                    advance();
        }

            }else{
                addToken(TokenType::SLASH);
            }
            break;

        case '"':
            scanString();
            break;

        default:

            if (isdigit(c)) {
                scanNumber();

            } else if (isAlpha(c)) {
                scanIdentifier();

            } else {
                Lox::error(
                    line,
                    "Unexpected character."
                );
            }

            break;
    }
}

vector<Token> Scanner::scanTokens(){
    while(!isAtEnd()){
        start=current;
        scanToken();
    }

    tokens.push_back(
        Token(TokenType::END_OF_FILE,"","",line)
    );

    return tokens;
}