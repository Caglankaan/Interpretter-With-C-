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
    std::string scan;
    std::cout << "Welcome to the ---- language\n";
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
        if(evaluated->which_object  != "Null" && evaluated->which_object != "")
        {
            std::string return_str = evaluated->Inspect(evaluated);
            std::cout << return_str << "\n";
        }
    }
}
