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
    
}

