#ifndef __AST_HEADER__
#define __AST_HEADER__

#include <iostream>
#include <vector>
#include "../token/token.h"

class Statement;

class Node
{
    public:
        std::string Value_type;
        int Value_int;
        bool Value_bool;
        std::string Value_string;
        Token token;
        std::string Value;
        std::string node_type;
        std::string which_identifier;
        std::string which_statement;
        std::string Operator;
        std::vector<Node *> Parameters_identifier;
        std::vector<Node *> Arguments_identifier;
        std::vector<Node *> Statements_statement; 
        std::vector<Node *> Statements_program; 
        Node *Right_identifier;
        Node *Left_identifier;
        Node *Condition_identifier;
        Node *Consequence_statement;
        Node *Alternative_statement;
        Node *Body_statement;
        Node *Function_identifier;
        Node *Name_identifier;
        Node *Value_identifier;
        Node *ReturnValue_identifier;
        Node *Expression_identifier;


        std::string TokenLiteral();
        std::string String();
        
};
class Expression: public Node
{
    public:
        std::string TokenLiteral(){}
        std::string String(){};
        void expressionNode();
};

class Identifier
{
    public:
        Token token;
        std::string Value;
        int Value_int;
        bool Value_bool;
        std::string Operator;                 
        Identifier *Right;                    //PrefixExpression
        Identifier *Left;                     //InfixExpression
        Identifier *Condition;                //IfExpression
        Statement *Consequence;               //IfExpression
        Statement *Alternative;               //IfExpression
        std::vector<Identifier *> parameters; //FunctionLiteral
        Statement *Body;                      //FunctionLiteral
        Identifier *Function;                 //CallExpression
        std::vector<Identifier *> Arguments;  //CallExpression

        std::string which_identifier;

        void expressionNode();

        std::string TokenLiteral();

        std::string String();
};
/*
class IntegerLiteral: public Identifier
{
    public:
        void statementNode(){}
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            std::cout << "IntegralLiteral string: " << token.Literal;
            return token.Literal;
        }
};

class PrefixExpression: public Identifier
{
    public:
        void statementNode(){}
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            std::cout << "PrefixExpression string: " << "("+Operator+Right->String()+")";
            return "("+Operator+Right->String()+")";
        }
};

class InfixExpression: public Identifier
{
    public:
        void statementNode(){}
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            return "("+Left->String()+" "+Operator+" "+Right->String()+")";
        }
};

class Boolean: public Identifier 
{
    public:
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            return token.Literal;
        }
};

class IfExpression: public Identifier
{
    //
};
*/

#endif