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
#define BREAK_OBJ "BREAK"
#define ERROR_OBJ "ERROR"
#define FUNCTION_OBJ "FUNCTION"
#define STRING_OBJ "STRING"
#define BUILTIN_OBJ "BUILTIN"
#define ARRAY_OBJ "ARRAY"
#define HASH_OBJ "HASH"

typedef std::string ObjectType;
//typedef std::function<Object(std::vector<Object *>)> BultinFunction;

class Env;

class HashKeyClass
{
    public:
        ObjectType Type;
        long Value;

        bool operator==(const HashKeyClass& m) const
        {
            bool xd = Type == m.Type && Value == m.Value;
            //std::cout << "buna mi giriyo ya, xd: " << xd << "\n";
            return xd;
        }
};

class MyHashFunction
{
    public:
        size_t operator()(const HashKeyClass& m) const
        {
            //std::cout << "yoksa buraya mı giriyo la\n";
            return m.Value + m.Type.length();
        }
};

class Object
{
    public:
        std::string which_object;
        std::string error_message;
        void *Value;
        std::vector<Node *> parameters;
        Node *body;
        MyEnv::Env *env;
        std::vector<Object *> elements;
        ObjectType type;
        int value_hash_int;
        Object *Key;
        std::unordered_map<HashKeyClass, Object*, MyHashFunction> HashPair;

        std::string Inspect(Object *o);
};

void setValStr(Object *obj, std::string &val);
void setValStr(Object *obj, char* val);
void setValLong(Object *obj, long &val);
void setValBool(Object *obj, bool &val);
void setValObj(Object *obj, Object *val_obj);
HashKeyClass GetHashKey(Object *key);

#endif