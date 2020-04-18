#ifndef __LEXER_HEADER__
#define __LEXER_HEADER__

#include <iostream>
#include "../token/token.h"
#include <string.h>

struct Lexer{
    std::string input;
    int position;
    int readPosition;
    char ch;
};


bool isLetter(char ch);
char peekChar(Lexer *l);
std::string readIdentifier(Lexer *l);
bool isDigit(char ch);
std::string readNumber(Lexer *l);
void skipWhitespace(Lexer *l);
Lexer *New(std::string input);
void readChar(Lexer *l);
Token nextToken(Lexer *l);

Token newToken(TokenType tokenType, std::string str);
Token newToken(TokenType tokenType, char byte);

#endif