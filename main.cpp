#include "evaluator/builtins.h"
#include "token/token.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "evaluator/evaluator.h"
#include "environment/environment.h"
#include <vector>

#define PROMPT = ">> "

void printParserErrors(std::vector<std::string> errors)
{
    for(auto& error: errors)
    {
        std::cout << "\t"+error+"\n";
    }
}

int main()
{
    /*
void registerBuiltinFunctions(std::string func_name, std::function<Object(std::vector<Object *>)> function)

Object builtinLenFunc(std::vector<Object *> arguments)
    */
    std::string scan;
    std::cout << "Welcome to the ___ language\n";
    
    Object (*lenFuncPtr)(std::vector<Object *> arguments);
    lenFuncPtr = &builtinLenFunc;
    registerBuiltinFunctions("len", lenFuncPtr);


    Object (*pushFuncPtr)(std::vector<Object *> arguments);
    pushFuncPtr = &builtinPushFunc;
    registerBuiltinFunctions("push", pushFuncPtr);


    Object (*printFuncPtr)(std::vector<Object *> arguments);
    printFuncPtr = &builtinPrintFunc;
    registerBuiltinFunctions("print", printFuncPtr);

    MyEnv::Env *env = MyEnv::newEnv();
    while(true)
    {
        std::cout << ">> ";
        std::getline(std::cin, scan);
        Lexer *l = New(scan);
        Parser *p = New(l);

        Node *program = ParseProgram(p);
    
        if(p->errors.size() != 0)
        {
            printParserErrors(p->errors);
            continue;
        }

        Object *evaluated = Eval(program, env);
        if(evaluated->which_object == STRING_OBJ || evaluated->which_object == INTEGER_OBJ || evaluated->which_object == RETURN_VALUE_OBJ
        || evaluated->which_object == ERROR_OBJ || evaluated->which_object == BOOLEAN_OBJ || evaluated->which_object == ARRAY_OBJ)
        {
            std::string return_str = evaluated->Inspect(evaluated);
            std::cout << return_str << "\n";
        }
        else if(evaluated->which_object == NULL_OBJ)
        {
            std::cout << "null" << "\n";
        }
        else if(evaluated->which_object == "")
        {
            std::string return_str = evaluated->Inspect(evaluated);
            std::cout <<"WHICH OBJECT EMPTY EGLDI: "<< return_str << "\n";
        }

    
        free(l);
        free(p);
    }
}


//while (true){print("x is: ", x); let x = x + 1; if(x == 2000000){break;}}
//while (true){print("x is: ",x)} yine memory hayvan gibi kullaniyor

//let factorial = fn(n) { if (n == 0) { 1 } else { n * factorial(n - 1) } };