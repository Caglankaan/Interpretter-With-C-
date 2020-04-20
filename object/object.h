#ifndef __OBJECT_HEADER__
#define __OBJECT_HEADER__

#include <iostream>
#include <vector>
#include <functional>
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
#define ARRAY_OBJ "ARRAY"
#define HASH_OBJ "HASH"

typedef std::string ObjectType;
//typedef std::function<Object(std::vector<Object *>)> BultinFunction;

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
        std::vector<Object *> elements;
        ObjectType type;
        int value_hash_int;
        Object *Key;
        std::unordered_map<Object*, Object*> HashPair;

        std::string Inspect(Object *o);
};


Object *HashKey(Object *key);

#endif