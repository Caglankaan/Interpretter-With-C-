#include "object.h"

std::string Object::Inspect(Object *o)
{
    if(o->which_object == INTEGER_OBJ)
    {
        return std::to_string((long) o->Value);
    }
    else if(o->which_object == BOOLEAN_OBJ)
    {
        return std::to_string((bool)o->Value);
    }
    else if(o->which_object == NULL_OBJ)
    {
        return "null";
    }
    else if(o->which_object == RETURN_VALUE_OBJ)
    {
        return Inspect((Object* )Value);
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
        char *val = (char*) o->Value;
        return std::string(val);
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
            el += vk.second->Key->Inspect(vk.second->Key) + ":" + vk.second->Inspect((Object* )vk.second->Value);
            i+=1;    
        }
        el +="}";
        return el;
    }
    
}

Object::~Object()
{
    delete body;
    delete env;
    delete Key;
    for(auto elem: elements)
        delete elem;
    for(auto vk: HashPair)
        delete vk.second;
    for(auto param: parameters)
        delete param;
    delete Value;
    parameters.clear();
    elements.clear();
    HashPair.clear();
}

HashKeyClass GetHashKey(Object *key)
{
    
    if(key->which_object == INTEGER_OBJ)
    {
        HashKeyClass *hash_key = new HashKeyClass();
        hash_key->Type = INTEGER_OBJ;
        hash_key->Value = (long)key->Value;
        
        return *hash_key;
    }
    
    HashKeyClass *hash_key = new HashKeyClass();
    hash_key->Type = STRING_OBJ;
    std::string key_val = std::string((char*)key->Value);
    std::size_t str_hash = std::hash<std::string>{}(std::string((char *)key->Value));
    hash_key->Value = static_cast<long>(str_hash);

    return *hash_key;
    
}

void setValStr(Object *obj, std::string &val)
{
    obj->Value = (void*)val.c_str();
}
void setValStr(Object *obj, char* val)
{
    obj->Value = (void*)val;
}
void setValLong(Object *obj, long &val)
{
    obj->Value = (void* )val;
}
void setValBool(Object *obj, bool &val)
{
    obj->Value = (void* )val;
}
void setValObj(Object *obj, Object *val_obj)
{
    obj->Value = (void *)val_obj;
}