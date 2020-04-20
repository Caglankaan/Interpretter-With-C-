#include "object.h"

std::string Object::Inspect(Object *o)
{
    if(o->which_object == INTEGER_OBJ)
    {
        return std::to_string(o->Value_int);
    }
    else if(o->which_object == BOOLEAN_OBJ)
    {
        return std::to_string(o->Value_bool);
    }
    else if(o->which_object == NULL_OBJ)
    {
        return "null";
    }
    else if(o->which_object == RETURN_VALUE_OBJ)
    {
        return Inspect(Value_object);
    }
    else if(o->which_object == ERROR_OBJ)
    {
        return "ERROR: ", o->error_message;
    }
    else if (o->which_object == FUNCTION_OBJ)
    {
        std::string inspect_func="fn(";
        for(int i = 0; i < parameters.size(); i++)
        {
            if(i > 0)
                inspect_func+=",";
            inspect_func += parameters[i]->String();
        }
        inspect_func +=") {\n" + body->String() + "\n}";
        return inspect_func;
    }
    else if(o->which_object == STRING_OBJ)
    {
        return o->Value_string;
    }
    else if(o->which_object == BUILTIN_OBJ)
    {
        return "builtin function";
    }
    else if(o->which_object == ARRAY_OBJ)
    {
        std::string el="[";
        for(int i = 0; i < elements.size(); i++)
        {
            if(i > 0)
                el+=",";
            el += elements[i]->Inspect(elements[i]);
        }
        el +="]";
        return el;
    }
    else if(o->which_object == HASH_OBJ)
    {
        std::string el="{";
        int i = 0;
        for(auto vk: HashPair)
        {
            if(i > 0)
                el+=", ";
            el += vk.first->Inspect(vk.first) + ":" + vk.second->Inspect(vk.second);
            i+=1;
        }
        el +="}";
        return el;
    }
    
}

Object *HashKey(Object *key)
{
    if(key->which_object == INTEGER_OBJ)
    {
        Object *hash_key = new Object();
        hash_key->type = INTEGER_OBJ;
        hash_key->value_hash_int = key->Value_int;
        return hash_key;
    }
    //else this is stringobject for sure
        Object *hash_key = new Object();
        hash_key->type = STRING_OBJ;
        hash_key->Value_string = key->Value_string;
        return hash_key;

}

