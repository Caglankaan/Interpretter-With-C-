#ifndef __OBJECT_HEADER__
#define __OBJECT_HEADER__

#include <iostream>
#include <vector>
#include "../token/token.h"
#include "../ast/ast.h"
#include "../environment/environment.h"

#define INTEGER_OBJ "INTEGER"
#define BOOLEAN_OBJ "BOOLEAN"
#define NULL_OBJ "NULL"
#define RETURN_VALUE_OBJ "RETURN"
#define ERROR_OBJ "ERROR"
#define FUNCTION_OBJ "FUNCTION"
#define STRING_OBJ "STRING"
#define BUILTIN_OBJ "BUILTIN"

typedef std::string ObjectType;

class Env;

class Object
{
    public:
        std::string which_object;
        std::string error_message;
        std::string Value_string;
        int Value_int;
        bool Value_bool;
        Object *Value_object;
        std::vector<Node *> parameters;
        Node *body;
        MyEnv::Env *env;

        std::string Inspect(Object *o);
};


#endif