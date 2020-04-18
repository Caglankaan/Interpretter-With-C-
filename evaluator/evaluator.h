#include "../ast/ast.h"
#include "../object/object.h"
#include "../environment/environment.h"

Object *Eval(Node *p, MyEnv::Env *env);
Object *boolObject(bool input);
Object *nullObject();
Object *evalBangOperatorExpression(Object *right);
Object *evalMinusPrefixOperatorExpression(Object *right);
Object *evalIntegerInfixExpression(std::string op, Object *left, Object *right);
Object *evalInfixExpression(std::string op, Object *left, Object *right);
Object *evalPrefixExpression(std::string op, Object *right);
Object *evalIfExpression(Node *if_expression, MyEnv::Env *env);
Object *evalProgram(Node *p, MyEnv::Env *env);
Object *evalBlockStatement(Node *p, MyEnv::Env *env);
Object *newErrorInfix(std::string left, std::string operator_between, std::string right);
Object *newErrorPrefix(std::string operator_between, std::string nodeType);

bool isError(Object *ob);
bool isTruthy(Object *obj);