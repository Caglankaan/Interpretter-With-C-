
#include "ast.h"
#include "statement.h"


std::string Statement::TokenLiteral()
{
    return token.Literal;
}
std::string Statement::String()
{
    if(which_statement == "LetStatement")
    {
        return TokenLiteral()+ " " + Name->String() + " = " + Value->String()+";";
    }
    else if(which_statement == "ReturnStatement")
    {
        return TokenLiteral() + " " + ReturnValue->String() + ";";
    }
    else if(which_statement == "ExpressionStatement")
    {
        return expression->String();
    }
    else if(which_statement == "BlockStatement")
    {
        std::string return_str;
        for(auto statement: Statements)
        {
            return_str += statement->String();
        }
        return return_str;
    }
    else
    {
        return "STATEMENT_ELSE_RETURN";
        
    }
    
}