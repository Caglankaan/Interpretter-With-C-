#include "../object/object.h"
#include "environment.h"


bool MyEnv::Env::isObjectSetted(std::string name)
{
    return store[name];
}

Object *MyEnv::Env::getObject(std::string name)
{
    Object *myobj = store[name];
    if(outer != NULL)
        myobj = outer->getObject(name);
        
    return myobj;
}

void MyEnv::Env::setObject(std::string name, Object *new_object)
{
    store[name] = new_object;
}

MyEnv::Env *MyEnv::newEnv()
{
    MyEnv::Env *env = new MyEnv::Env();
    std::unordered_map<std::string, Object*> store;
    env->store = store;
    env->outer = NULL;
    return env;
}

MyEnv::Env *MyEnv::newEnclosedEnv(MyEnv::Env *outer)
{
    MyEnv::Env *env = new MyEnv::Env();
    env->outer = outer;
    return env;
}