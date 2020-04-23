#include "builtins.h"
std::unordered_map<std::string, std::function<Object(std::vector<Object *>)>> builtin_functions;
void registerBuiltinFunctions(std::string func_name, std::function<Object(std::vector<Object *>)> function)
{
    builtin_functions[func_name] = function;
}

Object builtinLenFunc(std::vector<Object *> arguments)
{
    if(arguments.size() != 1)
    {
        std::cout << "verdiğin parametre sayisi 1 degil yapcagin isi sikim\n";
    }
    else
    {
        if(arguments[0]->which_object == STRING_OBJ)
        {
            Object *lenFunc = new Object();
            lenFunc->which_object = INTEGER_OBJ;
            long size = sizeof((char *)arguments[0]->Value)/sizeof(char);
            std::cout << "girdi buraya size: " << size << "\n";
            setValLong(lenFunc, size );
            
            return *lenFunc;
        }
        else if(arguments[0]->which_object == ARRAY_OBJ)
        {
            Object *lenFunc = new Object();
            lenFunc->which_object = INTEGER_OBJ;
            
            long vallong = arguments[0]->elements.size();
            setValLong(lenFunc, vallong);
            return *lenFunc;
        }
        else
        {
            std::cout << "verdigin parametre string degil yapcagin isi sikeyim\n";
        }
        
    }
}

Object builtinPushFunc(std::vector<Object *> arguments)
{
    if(arguments.size() != 2)
    {
        std::cout << "verdigin parametre sayisi 2 degil yapcagin isi sikim(array ve eleman ver)\n";
    }
    else
    {
        if(arguments[0]->which_object != ARRAY_OBJ)
        {
            std::cout << "verdigin ilk parametre array degil yapcagin isi sikim\n";
        }
        else
        {
            if(arguments[1]->which_object == STRING_OBJ)
            {
                Object *new_obj = new Object();
                new_obj->which_object = STRING_OBJ;

                setValStr(new_obj, (char *)arguments[1]->Value);
                arguments[0]->elements.push_back(new_obj);
            }
            else if(arguments[1]->which_object == INTEGER_OBJ)
            {
                Object *new_obj = new Object();
                new_obj->which_object = INTEGER_OBJ;
                long arg = (long)arguments[1]->Value;

                setValLong(new_obj, arg);
                arguments[0]->elements.push_back(new_obj);
            }
            else if(arguments[1]->which_object == ARRAY_OBJ)
            {
                Object *new_obj = new Object();
                new_obj->which_object = ARRAY_OBJ;
                new_obj->elements = arguments[1]->elements;
                arguments[0]->elements.push_back(new_obj);
            }
            
            else if(arguments[1]->which_object == BOOLEAN_OBJ)
            {
                Object *new_obj = new Object();
                new_obj->which_object = BOOLEAN_OBJ;

                bool arg = (long)arguments[1]->Value;
                setValBool(new_obj, arg);
                arguments[0]->elements.push_back(new_obj);

            }
            else
            {
                std::cout << "verdigin 2. parametre ne amınakoyim string array int yada bool degil yapcagin isi sikim\n";
            }
            
        }
        
    }
    
}

Object builtinPrintFunc(std::vector<Object *> arguments)
{
    
    for(auto &arg: arguments)
    {
        if(arg->which_object == STRING_OBJ)
        {
            std::cout << (char *)arg->Value;
        }
        else if(arg->which_object == INTEGER_OBJ)
        {
            std::cout << (long)arg->Value;
        }
        else if(arg->which_object == BOOLEAN_OBJ)
        {
            std::cout << (bool)arg->Value;
        }
        else
        {
            std::cout << arg->Inspect(arg);
        }
    }
    std::cout << "\n";
    
}