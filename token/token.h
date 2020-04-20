#ifndef __TOKEN_HEADER__
#define __TOKEN_HEADER__

#include <iostream>
#include <unordered_map>

#define ILLEGAL "ILLEGAL"
#define END_OF_FILE "END_OF_FILE"

// Identifiers + literals
#define IDENT "IDENT"
#define INT "INT"

// Operators
#define ASSIGN "="
#define PLUS "+"
#define MINUS "-"
#define BANG "!"
#define ASTERISK "*"
#define SLASH "/"
#define COLON ":"

#define LT "<"
#define GT ">"

#define EQ "=="
#define NOT_EQ "!="

// Delimiters
#define COMMA ","
#define SEMICOLON ";"

#define LBRACKET "["
#define RBRACKET "]"
#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"

// Keywords
#define FUNCTION "FUNCTION"
#define LET "LET"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define IF "IF"
#define ELSE "ELSE"
#define RETURN "RETURN"

#define STRING "STRING"

typedef std::string TokenType;

struct Token
{
    TokenType Type;
    std::string Literal;
};

extern std::unordered_map<std::string, TokenType> keywords;


TokenType LookupIdent(std::string ident);


#endif