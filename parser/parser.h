#ifndef __PARSER_HEADER__
#define __PARSER_HEADER_

#include "../ast/ast.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include <functional>
#include <string>

enum Precedences { LOWEST, EQUALS, LESSGREATER, SUM, PRODUCT, PREFIX, CALL, INDEX};

// typedef std::function<Node(Parser *p)> prefixParseFn;
// typedef std::function<Node(Parser *p)> infixParseFn;

struct Parser
{
    Lexer *l;
    std::vector<std::string> errors;
    Token curToken;
    Token peekToken;
    std::unordered_map<TokenType, std::function<Node(Parser *p)>> prefixParseFns;
    std::unordered_map<TokenType, std::function<Node(Parser *p, Node *left)>> infixParseFns;
};

Parser *New(Lexer *l);

Node *ParseProgram(Parser *p);

void registerPrefix(Parser *p, TokenType tokenType, std::function<Node(Parser *p)> fn);
void registerInfix(Parser *p, TokenType tokenType, std::function<Node(Parser *p, Node *left)> fn);
void nextToken(Parser *p);
void noPrefixParseFnError(Parser *p, TokenType t);
void peekError(Parser *p, TokenType t);

bool expectPeek(Parser *p, TokenType t);
bool curTokenIs(Parser *p, TokenType t);
bool peekTokenIs(Parser *p, TokenType t);

int curPrecedence(Parser *p);
int peekPrecedence(Parser *p);

std::vector<std::string> Errors(Parser *p);

Node *parseStatement(Parser *p);
Node *parseLetStatement(Parser *p);
Node *parseExpressionStatement(Parser *p);
Node *parseReturnStatement(Parser *p);
Node *parseBlockStatement(Parser *p);

Node parseWhileExpression(Parser *p);
Node parseIfExpression(Parser *p);
Node parseFunctionLiteral(Parser *p);
Node parseGroupExpression(Parser *p);
Node parseBoolean(Parser *p);
Node parseInfixExpression(Parser *p, Node *left);
Node parsePrefixExpression(Parser *p);
Node parseExpression(Parser *p, int precedence);
Node parseIdentifier(Parser *p);
Node parseInteger(Parser *p);
Node parseCallExpression(Parser *p, Node *function_identifier);
Node parseArrayLiteral(Parser *p);
Node parseIndexExpression(Parser *p);
Node parseHashLiteral(Parser *p);

std::vector<Node *> parseFunctionParameters(Parser *p);
std::vector<Node *> parseCallArguments(Parser *p);
std::vector<Node *> parseExpressionList(Parser *p, TokenType end);

#endif