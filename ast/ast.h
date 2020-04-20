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
        std::unordered_map<Node*, Node*> Pairs;
        std::vector<Node *> Parameters_identifier;
        std::vector<Node *> Arguments_identifier;
        std::vector<Node *> Statements_statement; 
        std::vector<Node *> Statements_program; 
        std::vector<Node *> Elements;
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
        Node *Left_index;
        Node *Right_index;
        Node *Index;


        std::string TokenLiteral();
        std::string String();
        
};

#endif