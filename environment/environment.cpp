#include "../object/object.h"
#include "environment.h"


bool MyEnv::Env::isObjectSetted(std::string name, MyEnv::Env *e)
{
    if(e->store[name])
        return true;
    return false;
}


Object *MyEnv::Env::getObject(std::string name, MyEnv::Env* e)
{

    if(e->store[name])
    {
        return e->store[name];
    }
    if(e->has_outer)
    {
        return getObject(name, e->outer);
    }
    
    Object *err = new Object();
    err->error_message = "identifier not found: " + name;
    err->which_object = ERROR_OBJ;
    return err;
}


void MyEnv::Env::setObject(std::string name, Object *new_object, Env* env)
{
    env->store[name] = new_object;
}

MyEnv::Env *MyEnv::newEnv()
{
    MyEnv::Env *env = new MyEnv::Env();
    std::unordered_map<std::string, Object*> store;
    env->store = store;
    env->outer = NULL;
    env->has_outer = false;
    return env;
}

MyEnv::Env *MyEnv::newEnclosedEnv(MyEnv::Env *outer)
{
    MyEnv::Env *env = MyEnv::newEnv();
    env->outer = outer;
    env->has_outer = true;
    return env;
}