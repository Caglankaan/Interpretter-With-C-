#include "evaluator.h"
#include "../object/object.h"
#include "../environment/environment.h"

Object *boolean_obj = new Object();
Object *null_obj = new Object();

bool isError(Object *obj)
{
    if(obj != NULL)
    {
        return obj->which_object == ERROR_OBJ;
    }
    return false;
}

Object *boolObject(bool input)
{
    boolean_obj->Value_bool = input;
    boolean_obj->which_object = BOOLEAN_OBJ;
    return boolean_obj;
}

bool isTruthy(Object *obj)
{
    if(obj->Value_bool)
        return 1;
    return 0;
}

Object *nullObject()
{
    null_obj->which_object = NULL_OBJ;
    return null_obj;
}

Object *evalBangOperatorExpression(Object *right)
{
    if(right->which_object == NULL_OBJ)
    {
        return boolObject(false);
    }
    else if(right->which_object == BOOLEAN_OBJ)
    {
        if(right->Value_bool)
            return boolObject(false);
        return boolObject(true);
    }
    return boolObject(false);
}

Object *evalMinusPrefixOperatorExpression(Object *right)
{
    if(right->which_object != INTEGER_OBJ)
    {
        return newErrorPrefix("-",right->which_object);
    }
    Object *val = new Object();
    val->Value_int = -right->Value_int;
}

Object *evalStringInfixExpression(std::string op, Object *left, Object *right)
{
    if(op != "+")
    {
        return newErrorInfix(left->which_object, op, right->which_object);
    }

    Object *str = new Object();
    str->Value_string = left->Value_string+right->Value_string;
    return str;
}

Object *evalIntegerInfixExpression(std::string op, Object *left, Object *right)
{

    Object *val = new Object();
    val->which_object = INTEGER_OBJ;
    if(op == "+")
    {
        val->Value_int = left->Value_int + right->Value_int;
        return val;
    }
    else if(op == "-")
    {
        val->Value_int = left->Value_int - right->Value_int;
        return val;
    }
    else if(op == "*")
    {
        val->Value_int = left->Value_int * right->Value_int;
        return val;
    }
    else if(op == "/")
    {
        val->Value_int = left->Value_int / right->Value_int;
        return val;
    }
    else if(op == "<")
    {
        return boolObject(left->Value_int < right->Value_int);
    }
    else if(op == "==")
    {
        return boolObject(left->Value_int == right->Value_int);
    }
    else if(op == "!=")
    {
        return boolObject(left->Value_int != right->Value_int);
    }
    else if(op == ">")
    {
        return boolObject(left->Value_int > right->Value_int);
    }
    else if(op == "<=")
    {
        return boolObject(left->Value_int <= right->Value_int);
    }
    else if(op == ">=")
    {
        return boolObject(left->Value_int >= right->Value_int);
    }
    return newErrorInfix(left->which_object, op, right->which_object);
}

Object *evalInfixExpression(std::string op, Object *left, Object *right)
{
    if(left->which_object == INTEGER_OBJ && right->which_object == INTEGER_OBJ)
    {
        return evalIntegerInfixExpression(op, left, right);
    }
    else if(left->which_object == STRING_OBJ && right->which_object == STRING_OBJ)
    {
        return evalStringInfixExpression(op, left, right);
    }
    else if(op == "==")
    {
        return boolObject(left == right);
    }
    else if(op == "!=")
    {
        return boolObject(left != right);
    }
    return newErrorInfix(left->which_object, op, right->which_object);
}

Object *evalPrefixExpression(std::string op, Object *right)
{
    if(op == "!")
        return evalBangOperatorExpression(right);
    else if(op == "-")
        return evalMinusPrefixOperatorExpression(right);
    return NULL;
}

Object *evalIfExpression(Node *if_expression, MyEnv::Env *env)
{
    Object *condition = Eval(if_expression->Condition_identifier, env);
    if(isError(condition))
        return condition;
    if(isTruthy(condition))
        return Eval(if_expression->Consequence_statement, env);
    else if(if_expression->Alternative_statement != NULL)
        return Eval(if_expression->Alternative_statement, env);
    return nullObject();
}


Object *evalProgram(Node *p, MyEnv::Env *env)
{
    Object *result = new Object();
    for(int i = 0; i < p->Statements_program.size(); i++)
    {
        result = Eval(p->Statements_program[i], env);
        if(result->which_object == RETURN_VALUE_OBJ)
            return result->Value_object;
        if(result->which_object == ERROR_OBJ)
            return result;
    }
    return result;
}

Object *evalBlockStatement(Node *p, MyEnv::Env *env)
{
    Object *result = new Object();
    for(int i = 0; i < p->Statements_statement.size(); i++)
    {
        result = Eval(p->Statements_statement[i], env);
        std::string type = result->which_object;
        if(type == ERROR_OBJ || type == RETURN_VALUE_OBJ)
            return result;
    }
    return result;
}

Object *newErrorInfix(std::string left, std::string operator_between, std::string right)
{
    Object *err = new Object();
    err->error_message = "type mismatch: " + left + " " + operator_between + " " + right;
    err->which_object = ERROR_OBJ;
    return err;
}

Object *newErrorIdentifier(std::string identifier)
{
    Object *err = new Object();
    err->error_message = "identifier not found: " + identifier;
    err->which_object = ERROR_OBJ;
    return err;
}

Object *newErrorPrefix(std::string operator_between, std::string nodeType)
{
    Object *err = new Object();
    err->error_message = "unknown operator: \"" + operator_between + "\" " + nodeType;
    err->which_object = ERROR_OBJ;
    return err;
}

Object *newErrorFunction(std::string nodeType)
{
    Object *err = new Object();
    err->error_message = "not a function: " + nodeType;
    err->which_object = ERROR_OBJ;
    return err;
}

Object *evalIdentifier(Node *p, MyEnv::Env *env)
{
    if(env->isObjectSetted(p->Value))
    {
        return env->getObject(p->Value);
    }
    return newErrorIdentifier(p->Value);
}

std::vector<Object *> evalExpressions(std::vector<Node *> args, MyEnv::Env *env)
{
    std::vector<Object *> results;
    Object *result = new Object();
    for(int i = 0; i < args.size(); i++)
    {
        result = Eval(args[i], env);
        if(isError(result))
        {
            results.clear();
            results.push_back(result);
            return results;
        }
        results.push_back(result);
    }
    return results;
}
MyEnv::Env *extendedFunctionEnv(Object *fun, std::vector<Object *> args)
{
    MyEnv::Env *env = MyEnv::newEnclosedEnv(fun->env);
    for(int i = 0; i < fun->parameters.size(); i++)
    {
        env->setObject(fun->parameters[i]->Value, args[i]);
    }

    return env;
}

Object *unwrapReturnValue(Object *obj)
{
    if(obj->which_object == "ReturnValue")
        return obj->Value_object;

    return obj;
}

Object *applyFunction(Object *fun, std::vector<Object *> args)
{
    if(fun->which_object != FUNCTION_OBJ){
        return newErrorFunction(fun->which_object);
    }
    MyEnv::Env *extendedEnv = extendedFunctionEnv(fun, args);
    Object *evaluated = Eval(fun->body, extendedEnv);
    return unwrapReturnValue(evaluated);
}

Object *Eval(Node *p, MyEnv::Env *env)
{
    if(p->node_type == "Statement")
    {
        if(p->which_statement == "ExpressionStatement")
            return Eval(p->Expression_identifier, env);
        else if(p->which_statement == "BlockStatement")
        {
            return evalBlockStatement(p, env);
        }
        else if(p->which_statement == "ReturnStatement")
        {
            Object *val = Eval(p->ReturnValue_identifier, env);
            if(isError(val))
            {
                return val;
            }
            Object *ret = new Object();
            ret->Value_object = val;
            ret->which_object = RETURN_VALUE_OBJ;
            return ret;
        }
        else if(p->which_statement == "LetStatement")
        {
            Object *val = Eval(p->Value_identifier, env);
            if(isError(val))
                return val;
            env->setObject(p->Name_identifier->Value, val);
        }
    }
    else if(p->node_type == "Identifier")
    {
        if(p->which_identifier == "PrefixExpression")
        {
            Object *right = Eval(p->Right_identifier, env);
            if(isError(right))
                return right;

           return evalPrefixExpression(p->Operator, right);
        }
        else if(p->which_identifier == "InfixExpression")
        {
            Object *left =  Eval(p->Left_identifier, env);
            Object *right = Eval(p->Right_identifier, env);
            if(isError(left))
                return left;
            else if(isError(right))
                return right;
            return evalInfixExpression(p->Operator, Eval(p->Left_identifier, env), Eval(p->Right_identifier, env));
        }
        else if(p->which_identifier == "IntegerLiteral")
        {
            Object *integ = new Object();
            integ->Value_int = p->Value_int;
            integ->which_object = INTEGER_OBJ;
            return integ;
        }
        else if(p->which_identifier == "Boolean")
        {
            return boolObject(p->Value_bool);
        }
        else if(p->which_identifier == "IfExpression")
        {
            return evalIfExpression(p, env);
        }
        else if(p->which_identifier == "FunctionLiteral")
        {
            Object *fun = new Object();
            fun->parameters = p->Parameters_identifier;
            fun->body = p->Body_statement;
            fun->which_object = FUNCTION_OBJ;
            return fun;
        }
        else if(p->which_identifier == "CallExpression")
        {
            Object *fun = Eval(p->Function_identifier, env);
            if(isError(fun))
                return fun;
            std::vector<Object *> args = evalExpressions(p->Arguments_identifier, env);
            if(args.size() == 1 && isError(args[0]))
            {
                return args[0];
            }

            return applyFunction(fun, args);
        }
        else if(p->which_identifier == "StringLiteral")
        {
            Object *str = new Object();
            str->Value_string = p->Value_string;
            str->which_object = STRING_OBJ;
            return str;
        }

        else if(p->which_identifier == "")
        {
            return evalIdentifier(p, env);
        }
    }
    else if(p->node_type == "Program")
    {
        return evalProgram(p, env);
    }
    else if(p->node_type == "Boolean")
    {
        return boolObject(p->Value_bool);
    }
}
