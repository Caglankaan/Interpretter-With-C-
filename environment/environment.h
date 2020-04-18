#ifndef __ENV_HEADER__
#define __ENV_HEADER__

#include <iostream>
#include <unordered_map>

class Object;

namespace MyEnv
{
    class Env
    {
        public:
            std::unordered_map<std::string, Object*> store;
            Env *outer;


            bool isObjectSetted(std::string name);
            Object *getObject(std::string name);
            void setObject(std::string name, Object *new_object);
            
    };

    Env *newEnv();
    Env *newEnclosedEnv(Env *outer);
}



#endif
