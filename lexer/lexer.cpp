#include "lexer.h"

Lexer *New(std::string input)
{
    Lexer *l = new Lexer();
    l->input = input;
    readChar(l);
    return l;
} 

void readChar(Lexer *l)
{
    if(l->readPosition >= l->input.size()){
        l->ch = 0;
    }
    else{
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition += 1;
}

std::string readString(Lexer *l)
{
    int position = l->position + 1;
    while(true)
    {
        readChar(l);
        if(l->ch == '"' || l->ch == 0)
            break;
    }
    return l->input.substr(position, l->position-position);
}

Token nextToken(Lexer *l)
{
    struct Token tok;

    skipWhitespace(l);
    

    switch(l->ch)
    {
        case '=':
            if(peekChar(l) == '=')
            {
                char ch = l->ch;
                readChar(l);
                std::string literal;
                literal.push_back(ch);
                literal.push_back(l->ch);
                tok = newToken(EQ, literal);
            }
            else
            {
                tok = newToken(ASSIGN, l->ch);
            }
            break;
        case '+':
            tok = newToken(PLUS, l->ch);
            break;
        case '-':
            tok = newToken(MINUS, l->ch);
            break;
        case '!':
            if(peekChar(l) == '=')
            {
                char ch = l->ch;
                readChar(l);
                std::string literal;
                literal.push_back(ch);
                literal.push_back(l->ch);
                tok = newToken(NOT_EQ, literal);
            }
            else
            {
                tok = newToken(BANG, l->ch);
            }
            break;
        case '/':
		    tok = newToken(SLASH, l->ch);
            break;
        case '*':
            tok = newToken(ASTERISK, l->ch);
            break;
        case '<':
            tok = newToken(LT, l->ch);
            break;
        case '>':
            tok = newToken(GT, l->ch);
            break;
        case ';':
            tok = newToken(SEMICOLON, l->ch);
            break;
        case '(':
            tok = newToken(LPAREN, l->ch);
            break;
        case ')':
            tok = newToken(RPAREN, l->ch);
            break;
        case ',':
            tok = newToken(COMMA, l->ch);
            break;
        case '{':
            tok = newToken(LBRACE, l->ch);
            break;
        case '}':
            tok = newToken(RBRACE, l->ch);
            break;
        case '"':
            tok.Type = STRING;
            tok.Literal = readString(l);
            break;
        case 0:
            tok.Literal = "";
            tok.Type = END_OF_FILE;
            break;
        default:
            if(isLetter(l->ch))
            {
                tok.Literal = readIdentifier(l);
                tok.Type = LookupIdent(tok.Literal);
                return tok;
            }
            else if(isDigit(l->ch))
            {
                tok.Type = INT;
                tok.Literal = readNumber(l);
                return tok;
            }
            else
            {
                tok = newToken(ILLEGAL, l->ch);
            }    
    }

    readChar(l);
    return tok;
}

std::string readNumber(Lexer *l)
{
    int position = l->position;
    while (isDigit(l->ch))
    {
        readChar(l);
    }
    return l->input.substr(position, l->position-position);
}

char peekChar(Lexer *l)
{
    if(l->readPosition >= l->input.size())
        return 0;
    return l->input[l->readPosition];
}

bool isDigit(char ch)
{
    return '0' <= ch && ch <= '9';
}

void skipWhitespace(Lexer *l)
{
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r')
        readChar(l);    
}

std::string readIdentifier(Lexer *l)
{
    int position = l->position;
    while(isLetter(l->ch)){
        readChar(l);
    }
    return l->input.substr(position, l->position-position);

    
}

Token newToken(TokenType tokenType, char byte)
{
    return Token{tokenType, std::to_string(byte)};
}

Token newToken(TokenType tokenType, std::string str)
{
    return Token{tokenType, str};
}

bool isLetter(char ch)
{
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}