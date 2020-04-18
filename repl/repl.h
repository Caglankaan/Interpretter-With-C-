#include "../lexer/lexer.h"
#include "../token/token.h"
#include <vector>

/*
#define PROMPT = ">> "


void printParserErrors(std::vector<std::string> errors)
{
    for(auto& error: errors)
    {
        std::cout << "\t"+error+"\n";
    }
}


void Start()
{
    std::string scan;
    std::cout << "Welcome to the ananizin ami language\n";
    std::cout << ">> ";
    std::getline(std::cin, scan);
    Lexer *l = New(scan);
    while(true)
    {
        struct Token tok;
        tok = nextToken(l);
        if(tok.Type == END_OF_FILE)
            break;
        std::cout << tok.Type << "\n";
    }
}
*/