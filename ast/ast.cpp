#include "ast.h"

std::string Node::TokenLiteral()
{
    return token.Literal;
}
std::string Node::String()
{
    if(node_type == "Identifier")
    {
        if(which_identifier == "IntegerLiteral")
        {
            return token.Literal;
        }
        else if(which_identifier == "PrefixExpression")
        {
            if(Operator == "")
            {
                return token.Literal;
            }
            return "("+Operator+Right_identifier->String()+")";
        }
        else if(which_identifier == "InfixExpression")
        {
            return "("+Left_identifier->String()+" "+Operator+" "+Right_identifier->String()+")";
        }
        else if(which_identifier == "Boolean")
        {
            return token.Literal;
        }
        else if(which_identifier == "IfExpression")
        {
            std::string return_if ="if" + Condition_identifier->String() + " " + Consequence_statement->String();
            if(Alternative_statement != NULL)
            {
                return_if += "else " + Alternative_statement->String();
            }

            return return_if;
        }
        else if(which_identifier == "FunctionLiteral")
        {
            std::string output_str = TokenLiteral()+"(";
            for(int i = 0; i < Parameters_identifier.size(); i++)
            {
                if(i > 0)
                    output_str += ",";
                output_str += Parameters_identifier[i]->String();
            }
            output_str += ") " +Body_statement->String();

            return output_str; 
        }
        else if(which_identifier == "CallExpression")
        {
            std::string output_str = Function_identifier->String() + "(";
            for(int i = 0; i < Arguments_identifier.size(); i++)
            {
                if(i > 0)
                    output_str += ",";
                output_str += Arguments_identifier[i]->String();
            }
            output_str += ")";
            return output_str;
        }
        else if(which_identifier == "ArrayLiteral")
        {
            std::string output_str = "[";
            for(int i = 0; i < Elements.size(); i++)
            {
                if(i > 0)
                    output_str += ",";
                output_str += Elements[i]->String();
            }
            output_str += "]";
            return output_str;
        }
        else if(which_identifier == "IndexExpression")
        {
            return "(" + Left_index->String() + "[" + Index->String() + "])";
        }
        else if(which_identifier == "HashLiteral")
        {
            std::string output_str = "{";
            int i = 0;
            for(auto vk: Pairs)
            {   
                if(i > 0)
                    output_str += ", ";
                output_str += vk.first->String() + ":" + vk.second->String();
                i+=1;
            }
            output_str += "}";
            return output_str;
        }
        
        return token.Literal;
    }
    else if(node_type == "Statement")
    {
        if(which_statement == "LetStatement")
        {
            return TokenLiteral()+ " " + Name_identifier->String() + " = " + Value_identifier->String()+";";
        }
        else if(which_statement == "ReturnStatement")
        {
            return TokenLiteral() + " " + ReturnValue_identifier->String() + ";";
        }
        else if(which_statement == "ExpressionStatement")
        {
            return Expression_identifier->String();
        }
        else if(which_statement == "BlockStatement")
        {
            std::string return_str;
            for(auto statement: Statements_statement)
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
    else if(node_type == "Program")
    {
        std::string my_str;
        for(auto& statement: Statements_program)
        {
            my_str = my_str + statement->String() + "\n";
        }
        return my_str;
    }
    else
    {
        return token.Literal;
    }
    
}
