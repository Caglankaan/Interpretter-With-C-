#include "evaluator.h"

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
    bool set = input;
    
    //boolean_obj->Value_bool = input;
    setValBool(boolean_obj, input);
    boolean_obj->which_object = BOOLEAN_OBJ;
    return boolean_obj;
}

bool isTruthy(Object *obj)
{
    //if(obj->Value_bool)
    if((bool)obj->Value)
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
        return boolObject(true);
    }
    else if(right->which_object == BOOLEAN_OBJ)
    {
        //if(right->Value_bool)
        if((bool)right->Value)
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
    val->which_object = INTEGER_OBJ;
    //val->Value_int = -right->Value_int;
    long right_value = (long)right->Value;
    val->Value = (void *) -right_value;
    return val;
}

Object *evalStringInfixExpression(std::string op, Object *left, Object *right)
{
    if(op != "+")
    {
        return newErrorInfix(left->which_object, op, right->which_object);
    }

    Object *str = new Object();
    str->which_object = STRING_OBJ;
    //str->Value_string = left->Value_string+right->Value_string;
    std::string leftplusright = std::string((char*) left->Value) + std::string((char*) right->Value);
    setValStr(str, leftplusright);
    return str;
}

Object *evalIntegerInfixExpression(std::string op, Object *left, Object *right)
{

    Object *val = new Object();
    val->which_object = INTEGER_OBJ;
    long total_value;
    if(op == "+")
    {
        total_value = (long)left->Value + (long)right->Value;
        setValLong(val, total_value);
        return val;
    }
    else if(op == "-")
    {
        total_value = (long)left->Value - (long)right->Value;
        setValLong(val, total_value);
        return val;
    }
    else if(op == "*")
    {
        total_value = (long)left->Value * (long)right->Value;
        setValLong(val, total_value);
        return val;
    }
    else if(op == "/")
    {
        total_value = (long)left->Value / (long)right->Value;
        setValLong(val, total_value);
        return val;
    }
    else if(op == "<")
    {
        delete val;
        return boolObject((long)left->Value < (long)right->Value);
    }
    else if(op == "==")
    {
        delete val;
        return boolObject((long)left->Value == (long)right->Value);
    }
    else if(op == "!=")
    {
        delete val;
        return boolObject((long)left->Value != (long)right->Value);
    }
    else if(op == ">")
    {
        delete val;
        return boolObject((long)left->Value > (long)right->Value);
    }
    else if(op == "<=")
    {
        delete val;
        return boolObject((long)left->Value <= (long)right->Value);
    }
    else if(op == ">=")
    {
        delete val;
        return boolObject((long)left->Value >= (long)right->Value);;
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
        return boolObject(left == right); //this probably returns false all the time.
    }
    else if(op == "!=")
    {
        return boolObject(left != right);//this probably returns false all the time.
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
    {
        delete condition;
        return Eval(if_expression->Consequence_statement, env);
    }
    else if(if_expression->Alternative_statement != NULL)
    {
        delete condition;
        return Eval(if_expression->Alternative_statement, env);
    }
    return nullObject();
}

Object *evalWhileExpression(Node *while_expression, MyEnv::Env *env)
{
    Object *condition = Eval(while_expression->Condition_identifier, env);
    if(isError(condition))
        return condition;
    if(isTruthy(condition))
    {
        delete condition;
        return Eval(while_expression->Consequence_statement, env);
    }
   
    return nullObject();
}


Object *evalProgram(Node *p, MyEnv::Env *env)
{
    Object *result = new Object();
    for(int i = 0; i < p->Node_array.size(); i++)
    {
        if(p->Node_array[i]->which_statement == "WhileStatement")
        {
            while(1)
            {
                if(result)
                    delete result;
                result = Eval(p->Node_array[i], env);
                if(result->which_object == RETURN_VALUE_OBJ)
                    return (Object *)result->Value;
                if(result->which_object == ERROR_OBJ)
                    return result;
                if(result->which_object == BREAK_OBJ)
                    break;
                
            }
        }
        else
        {
            delete result;
            result = Eval(p->Node_array[i], env);
            if(result->which_object == RETURN_VALUE_OBJ)
                return (Object *)result->Value;
            if(result->which_object == ERROR_OBJ)
                return result;
                
            
        }
    }
    return result;
}

Object *evalBlockStatement(Node *p, MyEnv::Env *env)
{
    Object *result = new Object();
    for(int i = 0; i < p->Node_array.size(); i++)
    {
        if(i < p->Node_array.size()-1)
            delete result;
        
        result = Eval(p->Node_array[i], env);
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
Object *newErrorIndex(std::string nodeType)
{
    Object *err = new Object();
    err->error_message = "index operator not supported: " + nodeType;
    err->which_object = ERROR_OBJ;
    return err;
}

Object *newNoValueFoundError(std::string nodeType)
{
    Object *err = new Object();
    err->error_message = "Not settet key: " + nodeType+" in map!";
    err->which_object = ERROR_OBJ;
    return err;
}

Object *newErrorOutOfRange()
{
    Object *err = new Object();
    err->error_message = "index out of range";
    err->which_object = ERROR_OBJ;
    return err;
}

Object *evalArrayIndexExpression(Object *arr, Object *index)
{
    long indx = (long)index->Value;
    long max = arr->elements.size() -1;

    if(indx < 0 || indx > max)
    {
        Object *nullobj = new Object();
        null_obj->which_object = NULL_OBJ;
        return null_obj;
    }
        
    return arr->elements[indx];
}


Object *evalHashLiteral(Node *node, MyEnv::Env *env)
{
    Object *returnObj = new Object();
    std::unordered_map<HashKeyClass, Object*, MyHashFunction> pairs;
    for(auto vk: node->Pairs)
    {
        Object *key = Eval(vk.first, env);
        if(isError(key))
        {
            
            return key;
        }
        if(key->which_object != STRING_OBJ && key->which_object != INTEGER_OBJ)
        {
            std::cout << "unusabla as hash key !!! " << key->which_object << "\n";
        }

        Object *value = Eval(vk.second, env);

        if(isError(value))
        {
            return value;
        }

        Object *hash_pair = new Object();
        hash_pair->Key = key;
        hash_pair->which_object = value->which_object;
        setValObj(hash_pair, value);
        delete value;
    
        pairs[GetHashKey(key)] = hash_pair;

    }
    
    returnObj->HashPair = pairs;
    returnObj->which_object = HASH_OBJ;
    return returnObj;
}

Object *evalHashIndexExpression(Object *left, Object* index)
{
    HashKeyClass get = GetHashKey(index);
    if(left->HashPair[get])
    {
        return (Object*) left->HashPair[get]->Value;
    }
    return newNoValueFoundError((char *)index->Value);
}

Object *evalIndexExpression(Object *left, Object *index)
{
    if(left->which_object == ARRAY_OBJ && index->which_object == INTEGER_OBJ)
    {
        return evalArrayIndexExpression(left, index);
    }
    else if(left->which_object == HASH_OBJ)
    {
        return evalHashIndexExpression(left, index);
    }

    return newErrorIndex(left->which_object);
}

Object *evalIdentifier(Node *p, MyEnv::Env *env)
{
    if(!env->store[p->Value])
    {
        if(builtin_functions[p->Value])
        {
            //std::vector<Object *> arg_array;
            //arg_array.push_back(new Object());
            //Object *returnObj = new Object(builtin_functions[p->Value](arg_array));
            //return returnObj;
        }
    }
    return env->getObject(p->Value, env);
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
            //results.push_back(result);  //buraya bakilacak
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
        env->setObject(fun->parameters[i]->Value, args[i], env);
    }

    return env;
}

Object *unwrapReturnValue(Object *obj)
{
    if(obj->which_object == "ReturnValue")
        return (Object *)obj->Value;

    return obj;
}

Object *applyFunction(Object *fun, std::vector<Object *> args)
{
    if(fun->which_object == FUNCTION_OBJ)
    {
        MyEnv::Env *extendedEnv = extendedFunctionEnv(fun, args);
        Object *evaluated = Eval(fun->body, extendedEnv);
        delete extendedEnv;
        return unwrapReturnValue(evaluated);
    }
    return newErrorFunction(fun->which_object);
}

Object *Eval(Node *p, MyEnv::Env *env)
{
    if(p->node_type == "Statement")
    {
        if(p->which_statement == "ExpressionStatement" || p->which_statement == "WhileStatement")
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
            
            setValObj(ret, val);

            ret->which_object = RETURN_VALUE_OBJ;
            return ret;
        }
        else if(p->which_statement == "LetStatement")
        {
            Object *val = Eval(p->Value_identifier, env);
            if(isError(val))
                return val;
            env->setObject(p->Name_identifier->Value, val, env);
            
        }
        else if(p->which_statement == "BreakStatement")
        {
            Object *break_obj = new Object();
            break_obj->which_object = BREAK_OBJ;
            return break_obj;
        }
        else{
            std::cout << "p->whixh_identişfier? : " << p->which_identifier<<"\n";
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
                
            return evalInfixExpression(p->Operator, left, right);
        }
        else if(p->which_identifier == "IntegerLiteral")
        {
            Object *integ = new Object();
            long p_val = (long) p->Value_int;
            setValLong(integ, p_val);
            //integ->Value_int = p->Value_int;
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
        else if(p->which_identifier == "WhileExpression")
        {
            return evalWhileExpression(p, env);
        }
        else if(p->which_identifier == "FunctionLiteral")
        {
            Object *fun = new Object();
            fun->parameters = p->Node_array;
            fun->body = p->Body_statement;
            fun->which_object = FUNCTION_OBJ;
            fun->env = env;
            return fun;
        }
        else if(p->which_identifier == "CallExpression")
        {
            if(builtin_functions[p->Function_identifier->Value])
            {
                std::vector<Object *> args = evalExpressions(p->Node_array, env);
                Object *returnObj = new Object(builtin_functions[p->Function_identifier->Value](args));
                /*for(auto arg: args)
                    delete arg;
                args.clear();
                */
                return returnObj;
            }
            Object *fun = Eval(p->Function_identifier, env);
            if(isError(fun))
                return fun;
            std::vector<Object *> args = evalExpressions(p->Node_array, env);
            if(args.size() == 1 && isError(args[0]))
            {
                return args[0];
            }

            return applyFunction(fun, args);
        }
        else if(p->which_identifier == "StringLiteral")
        {
            Object *str = new Object();
            setValStr(str, p->Value_string);
            str->which_object = STRING_OBJ;
            return str;
        }
        else if(p->which_identifier == "ArrayLiteral")
        {
            std::vector<Object *> elements = evalExpressions(p->Node_array, env);
            if(elements.size() == 1 && isError(elements[0]))
                return elements[0];
            Object *arr = new Object();
            arr->elements = elements;
            arr->which_object = ARRAY_OBJ;

            return arr;
        }
        else if(p->which_identifier == "IndexExpression")
        {
            Object *left =  Eval(p->Left_index, env);
            if(isError(left))
            {
                return left;
            }
            Object *index =  Eval(p->Index, env);
            if(isError(index))
            {
                return index;
            }
            return evalIndexExpression(left, index);
        }
        else if(p->which_identifier == "HashLiteral")
        {
            return evalHashLiteral(p, env);
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
