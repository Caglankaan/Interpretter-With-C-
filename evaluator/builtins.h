#ifndef __BULTINS_HEADER__
#define __BULTINS_HEADER__

#include <unordered_map>
#include <functional>
#include "../object/object.h"

extern std::unordered_map<std::string, std::function<Object(std::vector<Object *>)>> builtin_functions;

void registerBuiltinFunctions(std::string func_name, std::function<Object(std::vector<Object *>)> function);

Object builtinLenFunc(std::vector<Object *> arguments);
Object builtinPushFunc(std::vector<Object *> arguments);

#endif