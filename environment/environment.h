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
            bool has_outer;


            bool isObjectSetted(std::string name, MyEnv::Env *e);
            Object *getObject(std::string name, Env* e);
            void setObject(std::string name, Object *new_object, Env* env);
            
    };

    Env *newEnv();
    Env *newEnclosedEnv(Env *outer);
}



#endif
