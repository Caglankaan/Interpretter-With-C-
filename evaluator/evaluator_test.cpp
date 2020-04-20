#include "../ast/ast.h"
#include "../lexer/lexer.h"
#include "../object/object.h"
#include "../parser/parser.h"
#include "evaluator.h"


bool testIntegerObject(Object *evaluated, int expected)
{
    if(evaluated->which_object != INTEGER_OBJ && evaluated->which_object != RETURN_VALUE_OBJ)
    {
        std::cout << "obj type is not integer, type is: " << evaluated->which_object << "\n";
        return false;
    }
    if(evaluated->Value_int != expected)
    {
        if(evaluated->which_object == RETURN_VALUE_OBJ)
        {
            if(evaluated->Value_object->Value_int != expected)
            {
                std::cout << "object has wrong value, got: " << evaluated->Value_object->Value_int<< " expected: " << expected << "\n";
                return false;
            }
            return true;
        }
        std::cout << "object has wrong value, got: " << evaluated->Value_int<< " expected: " << expected << "\n";
        return false;
    }
    return true;
}

bool testBooleanObject(Object *evaluated, bool expected)
{
    if(evaluated->which_object != BOOLEAN_OBJ)
    {
        std::cout << "obj type is not integer, type is: " << evaluated->which_object << "\n";
        return false;
    }
    if(evaluated->Value_bool != expected)
    {
        std::cout << "Object has wrong value, got: " << evaluated->Value_bool << " expected: " << expected << "\n";
        return false;
    }

    return true;
}

Object *testEval(std::string input, MyEnv::Env *env)
{
    Lexer *l = New(input);
    Parser *p = New(l);

    Node *program = ParseProgram(p);

    return Eval(program, env);
}

void TestEvalIntegerExpression(MyEnv::Env *env)
{
    std::vector<std::string> tests = {"5","10","-5","-10","23","-32","5+5+5+5-10","2 * 2 * 2 * 2 * 2","-50 + 100 + -50","5 * 2 + 10","5 + 2 * 10", "20+2*10","20+2*-10","50/2*2+10","2*(5+10)","3*3*3+10","3*(3*3)+10","(5+10*2+15/3)*2+ -10"};
    std::vector<int> expected_outputs = {5, 10, -5, -10, 23, -32, 10, 32,0,20,25,0,60,30,37,37,50};

    for(int i = 0; i < tests.size(); i++)
    {
        Object *evaluated = testEval(tests[i], env);
        evaluated->which_object = INTEGER_OBJ;
        testIntegerObject(evaluated, expected_outputs[i]);
    }
}

void TestEvalBooleanExpression(MyEnv::Env *env)
{
    std::vector<std::string> tests = {"true","false"};
    std::vector<bool> expected_outputs = {true,false};

    for(int i = 0; i < tests.size(); i++)
    {
        Object *evaluated = testEval(tests[i], env);
        evaluated->which_object = BOOLEAN_OBJ;
        testBooleanObject(evaluated, expected_outputs[i]);
    }
}

void TestBangOperator(MyEnv::Env *env)
{
    std::vector<std::string> tests = {"!true","!false","!5","!!true","!!false","!!5"};
    std::vector<bool> expected_outputs = {false, true, false, true, false, true};
    
    for(int i = 0; i < tests.size(); i++)
    {
        Object *evaluated = testEval(tests[i], env);
        evaluated->which_object = BOOLEAN_OBJ;
        testBooleanObject(evaluated, expected_outputs[i]);
    }
}

void TestReturnStatements(MyEnv::Env *env)
{
    std::vector<std::string> tests = {"return 10;","return 10; 9;","return 2*5+9;","9; return 2*5; 5;"};
    std::vector<int> expected_outputs = {10, 10, 19, 10};
    
    for(int i = 0; i < tests.size(); i++)
    {
        Object *evaluated = testEval(tests[i], env);
        //evaluated->which_object = "Return";
        testIntegerObject(evaluated, expected_outputs[i]);
    }
}

void TestErrorHandling(MyEnv::Env *env)
{
    std::vector<std::string> tests = {"5+true;","5+true;5;","-true","true + false;","if(10>1) { true + false; }", "if (10 > 1) { if (10 > 1) { return true + false; } return 1; }"};

    for(int i = 0; i < tests.size(); i++)
    {
        Object *eval = testEval(tests[i], env);
        if(eval->which_object != ERROR_OBJ)
        {
            std::cout << "there is no error, good to go\n";
        }
        else
        {
            std::cout << eval->Inspect(eval) << "\n";
        }   
    }
}

void TestFunctionObject(MyEnv::Env *env)
{
    std::string input = "fn(x) {x +2;};";
    Object *eval = testEval(input, env);

    if(eval->which_object != FUNCTION_OBJ)
    {
        std::cout << "obj is not function, obj is: " << eval->which_object << "\n";
    }
    if(eval->parameters.size() != 1 )
    {
        std::cout << "parameter size is not 1\n";
    }
    if(eval->parameters[0]->String() != "x")
    {
        std::cout << "parameter is not x !\n";
    }
    std::string expected_body = "(x + 2)";
    std::string my_body = eval->body->String();
    if(my_body != expected_body)
    {
        std::cout << "body is not equal to expected body, body is: " <<my_body << "\n";
    }

}

int main()
{
    TestFunctionObject(MyEnv::newEnv());
}