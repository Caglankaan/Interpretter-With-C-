#ifndef __STATEMENT_HEADER__
#define __STATEMENT_HEADER__

#include <iostream>
#include <vector>
#include "../token/token.h"

class Identifier;

class Statement
{
    public:
        Token token;
        int int_value;
        Identifier *Name;
        Identifier *Value;      //let statement
        Identifier *ReturnValue; //returnstatement
        Identifier *expression;  //expressionstatement
        std::string which_statement;
        std::vector<Statement*> Statements; 

        std::string TokenLiteral();
        
        std::string String();

        void statementNode();
};

class LetStatement: public Statement
{
    public:
        void statementNode(){}
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            return TokenLiteral()+ " " + Name->String() + " = " + Value->String()+";";
        }
};

class ReturnStatement: public Statement
{
    public:
        void statementNode(){}
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            return TokenLiteral() + " " + ReturnValue->String() + ";";
        }
};

class ExpressionStatement: public Statement
{
    public:
        void statementNode(){}
        std::string TokenLiteral()
        {
            return token.Literal;
        }

        std::string String()
        {
            return expression->String();
        }
};

class BlockStatement: public Statement
{
 //
};

class Program
{
    public:
        std::vector<Statement *> Statements;
        std::string TokenLiteral()
        {
            if(Statements.size() > 0)
            {
                return Statements[0]->TokenLiteral();
            }
            return "";
        }

        std::string String()
        {
            std::string my_str;
            for(auto& statement: Statements)
            {
                my_str = my_str + statement->String() + "\n";
            }
            return my_str;
        }

};

#endif