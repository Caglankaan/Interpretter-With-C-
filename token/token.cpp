#include "token.h"

std::unordered_map<std::string, TokenType> keywords({
        {"fn", FUNCTION},
        {"let", LET},
        {"true", TRUE},
        {"false", FALSE},
        {"if", IF},
        {"else", ELSE},
        {"return", RETURN},
        {"while", WHILE},
        {"break", BREAK}
    });

TokenType LookupIdent(std::string ident)
{
    if(keywords.count(ident) > 0)
        return keywords[ident];
    
    return IDENT;
}