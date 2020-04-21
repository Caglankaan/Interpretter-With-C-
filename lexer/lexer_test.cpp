#include "../token/token.h"
#include "lexer.h"

#include "../repl/repl.h"
#include "../parser/parser.h"

void checkParserErrors(Parser *p)
{
    std::vector<std::string> errors = Errors(p);
    if(errors.size() == 0)
        return;

    std::cout << "Parser has " << errors.size() << " errors.\n";
    for(auto& err: errors)
    {
        std::cout << "Parser error: " << err << "\n";
    }
    exit(1);
}

bool TestLetStatement(Node *stmt, std::string expected)
{
    if(stmt->TokenLiteral() != "let")
    {
        std::cout << "token literal is not let !!!!" << stmt->TokenLiteral() << "\n";
        return false;
    }
    if(stmt->Name_identifier->Value != expected)
    {
        std::cout << "expected is: " << expected << "\n";
        std::cout << "name is not *ast.letstatement??: " << stmt->Name_identifier->Value << "\n";
        return false;
    }

    if(stmt->Name_identifier->TokenLiteral() != expected)
    {
        std::cout << "name is not "<<expected <<" name is:" << stmt->Name_identifier->TokenLiteral() << "\n";
        return false;
    }

    return true;
}

bool TestIdentifier(Node *i, std::string val)
{
    if(i->Value != val)
    {
        std::cout << "given val is not equal to expected val\n";
        return false;
    }
    if(i->TokenLiteral() != val)
    {
        std::cout << "given val.tokenliteral is not equal to expected val\n";
        return false;
    }
    return true;

}



void TestString()
{
    Node *program = new Node();
    Node *statement = new Node();
    Node *identifier = new Node();
    Node *identifier2 = new Node();

    statement->token.Type = LET;
    statement->token.Literal = "let";

    identifier->token.Type = IDENT;
    identifier->token.Literal = "myVar";
    identifier->Value = "myVar";

    identifier2->token.Type = IDENT;
    identifier2->token.Literal = "anotherVar";
    identifier2->Value = "anotherVar";

    statement->Name_identifier = identifier;

    statement->Value_identifier = identifier2;

    program->Statements_program.push_back(statement);

    std::cout << "program.string: \n\n" << program->String() << "\n";
}



void TestNextToken()
{
    //std::string input = "let five = 5; let ten = 10; let add = fn(x, y) {\nx + y;\n}; let result = add(five, ten); !-/*5;5 < 10 > 5;\nif(5<10){return 5 == 10 ;} else{ return 10 != 9;}";
    std::string input = "\"foobar\";\"foo bar\";";
    Lexer *l = New(input);
    for(int i = 0; i < input.size()+10; i++)
    {
        Token tok = nextToken(l);
        if(tok.Type == "END_OF_FILE")
            break;
    }

}

void TestIdentifierExpression()
{
    std::string input = "foobar;";
    Lexer *l = New(input);
    Parser *p = New(l);

    Node *program = ParseProgram(p);
    checkParserErrors(p);
    if(program == NULL)
    {
        std::cout << "null bu\n";
    }
    if(program->Statements_program.size() != 1 )
        std::cout << "program statements does not contains 1 statements!!!!" << " " << program->Statements_program.size();


    //if(program->Statements_program[0]->Expression_identifier->TokenLiteral() != "foobar")
    if(program->Statements_program[0]->Expression_identifier->TokenLiteral() != "foobar")
    {
        std::cout << "ident is not foobar. "<< program->Statements_program[0]->TokenLiteral() << "\n";
    }

    if(program->Statements_program[0]->Expression_identifier->Value != "foobar")
    {
        std::cout << "ident.value is not foobar.: " << program->Statements_program[0]->Expression_identifier->Value << "\n";
    }
    
}
bool testIntegerLiteral(Node *il, int value)
{
    if(il->Value_int != value)
    {
        std::cout <<"integ.value not: " << value << " value is: " << il->Value_int << "\n";
        return false;
    }
    if(il->TokenLiteral() != std::to_string(value))
    {
        std::cout << "integ.tokenliteral is not: " << value << " is: " << il->TokenLiteral() << "\n";
        return false;
    }
    return true;
}
void TestIntegerLiteralExpression()
{
    std::string input = "5;";
    Lexer *l = New(input);
    Parser *p = New(l);

    Node *program = ParseProgram(p);
    checkParserErrors(p);
    if(program == NULL)
    {
        std::cout << "null bu\n";
    }
    if(program->Statements_program.size() != 1 )
        std::cout << "program statements does not contains 1 statements!!!!" << " " << program->Statements_program.size();

    if(program->Statements_program[0]->Expression_identifier->Value_int != 5)
    {
        std::cout <<" some error occured value is not 5: "<< program->Statements_program[0]->Expression_identifier->Value_int << "\n";
    }
    if(program->Statements_program[0]->Expression_identifier->TokenLiteral() != "5")
    {
        std::cout <<" some error occured literal is not 5: "<< program->Statements_program[0]->Expression_identifier->Value_int << "\n";
    }
}

void TestParsingPrefixExpressions()
{
    std::vector<std::string> input_arr = {"!5;","-15;"};
    std::vector<std::string> operator_arr = {"!","-"};
    std::vector<int> integer_value_arr = {5,15};

    for(int i = 0; i < input_arr.size(); i++)
    {
        Lexer *l = New(input_arr[i]);
        Parser *p = New(l);

        Node *program = ParseProgram(p);
        checkParserErrors(p);

        if(program->Statements_program.size() != 1 )
            std::cout << "program statements does not contains 1 statements!!!!" << " " << program->Statements_program.size();

        if(program->Statements_program[0]->Expression_identifier->Operator != operator_arr[i])
        {
            std::cout << "exp.operator is not: " << operator_arr[i] << "operator is: " << program->Statements_program[0]->Expression_identifier->Operator << "\n";
        }

        if(!testIntegerLiteral(program->Statements_program[0]->Expression_identifier->Right_identifier, integer_value_arr[i]))
        {
            return;
        }
    }
}

bool testBooleanLiteral(Node *e, bool val)
{
    if(e->Value_bool != val)
    {
        std::cout << "e.value_bool is not equal to the expected boolean value \n";
        return false;
    }
    if(e->TokenLiteral() != std::to_string(val))
    {
        std::cout << "tokenliteral is not equal to the expected boolean, literal:" << e->TokenLiteral() << " val: " << std::to_string(val) << "\n";
        //return false;
    }
    return true;
}

bool testLiteralExpression(Node *e, std::string expected)
{
    bool is_int = false;
    int i;
    try
    {
        i = std::stoi(expected);
        is_int = true;
    }
    catch(const std::exception& exception)
    {
        is_int = false;
    }
    
    if(is_int)
    {
        return testIntegerLiteral(e, i);
    }
    else
    {
        if(expected == "true")
        {
            return testBooleanLiteral(e, true);
        }
        else if(expected ==" false")
        {
            return testBooleanLiteral(e, false);
        }
        else
        {
            return TestIdentifier(e, expected);
        }
    }
    std::cout << "testliteral expression is false\n";
    return false;
    
}

bool testInfixExpression(Node *e, std::string left, std::string given_op, std::string right)
{
    if(!testLiteralExpression(e->Left_identifier, left))
    {
        std::cout <<"testInfixExpression returned false,left\n";
        return false;
    }
    if(e->Operator != given_op)
    {
        std::cout <<"operators are not similar\n";
        return false;
    }
    if(!testLiteralExpression(e->Right_identifier, right))
    {
        std::cout <<"testInfixExpression returned false,right\n";
        return false;
    }

    return true;
}

void TestOperatorPrecedenceParsing()
{
   std::vector<std::string> input_arr = {"a + add( b * c ) +d", "add(a, b, 1, 2 * 3, 4 + 5, add(6, 7 * 8))", "add(a + b + c * d / f + g)"};

    //std::vector<std::string> input_arr = {"-a*b", "!-a","a+b+c","a+b-c","a+b*c","a*b/c","a+b/c","a+b*c+d/e-f","3+4; -5*5","5>4 == 3<4", "3+4*5 == 3*1+4*5","3+4*5 ==3*1+4*5"};
    //std::vector<std::string> input_arr = {"1 + (2+3) + 4", "((1+(2+3)) + 4)", "(5+5)*2", "2/(5+5)", "-(5+5)", "!(true == true)"};
    //std::vector<std::string> input_arr = {"!(false == true)"};
    //std::vector<std::string> output_arr = {"((-a) * b)"};
    for(int i = 0; i < input_arr.size(); i++)
    {
        Lexer *l = New(input_arr[i]);
        Parser *p = New(l);

        Node *program = ParseProgram(p);
        checkParserErrors(p);
        std::string actual = program->String();
        std::cout << "Given equation: " << input_arr[i] << " parsed equation: " << actual << "\n";
        
    }
}


void TestIfExpression()
{
    std::string input = " if(x < y)          {a}";
    Lexer *l = New(input);
    Parser *p = New(l);

    Node *program = ParseProgram(p);

    checkParserErrors(p);


    if(!testInfixExpression(program->Statements_program[0]->Expression_identifier->Condition_identifier, "x", "<", "y"))
    {
        std::cout << "test infix expression failed\n";
        return;
    }
}

void TestFunctionalLiteralParsing()
{
    std::string input = "fn(x,y) {x + y;}";
    Lexer *l = New(input);
    Parser *p = New(l);

    Node *program = ParseProgram(p);

    checkParserErrors(p);

    testLiteralExpression(program->Statements_program[0]->Expression_identifier->Node_array[0],"x");
    testLiteralExpression(program->Statements_program[0]->Expression_identifier->Node_array[1],"y");

    testInfixExpression(program->Statements_program[0]->Expression_identifier->Body_statement->Expression_identifier, "x","+","y");
}

void TestFunctionParameterParsing()
{
    std::vector<std::string> inputs = {"fn() {};", "fn(x) {};", "fn(x,y,z) {};"};
    std::vector<std::vector<std::string>> expected_params = {{},{"x"},{"x","y","z"}};
    for(int j = 0; j < inputs.size(); j++)
    {
        Lexer *l = New(inputs[j]);
        Parser *p = New(l);

        Node *program = ParseProgram(p);

        checkParserErrors(p);

        for(int i = 0; i < expected_params.size();i++)
        {
            testLiteralExpression(program->Statements_program[0]->Expression_identifier->Node_array[i], expected_params[j][i]);
        }
    }
}

void TestCallExpressionParsing()
{
    std::string input = "add(1,2*3,4+5);";
    Lexer *l = New(input);
    Parser *p = New(l);

    Node *program = ParseProgram(p);

    checkParserErrors(p);

    if(!TestIdentifier(program->Statements_program[0]->Expression_identifier->Function_identifier, "add"))
    {
       std::cout << "func name is not add, something wrong!!\n";
    }


    if(program->Statements_program[0]->Expression_identifier->Node_array.size() != 3)
    {
        std::cout << "Args size is not 3, is: " << program->Statements_program[0]->Expression_identifier->Node_array.size() << " something wrong!\n";
    }
    testLiteralExpression(program->Statements_program[0]->Expression_identifier->Node_array[0], "1");
    testInfixExpression(program->Statements_program[0]->Expression_identifier->Node_array[1],"2","*","3");
    testInfixExpression(program->Statements_program[0]->Expression_identifier->Node_array[2], "4","+","5");
}   

void TestReturnStatement()
{
    
    std::vector<std::string> inputs = {"return 5;","return true;","return foobar;"};
    std::vector<std::string> expected_output = {"5","true","foobar"};

    for(int i = 0; i < inputs.size(); i++)
    {
        Lexer *l = New(inputs[i]);
        Parser *p = New(l);

        Node *program = ParseProgram(p);

        checkParserErrors(p);

        if(program->Statements_program[0]->TokenLiteral() != "return")
        {
            std::cout << "token literal is not return, literal is: " << program->Statements_program[0]->TokenLiteral() << " something wrong\n";
        }

        if(!testLiteralExpression(program->Statements_program[0]->ReturnValue_identifier, expected_output[i]))
        {
            std::cout << "testliteral expression failed\n";
        }
    }
}


void testLetStatements()
{
    std::vector <std::string> inputs = {"let x = 5;", "let y = true;", "let foobar = y;"};
    std::vector <std::string> expected_identifier = {"x","y","foobar"};
    std::vector <std::string> expected_value = {"5","true","y"};
    
    for(int i = 0; i < inputs.size(); i++)
    {
        Lexer *l = New(inputs[i]);
        Parser *p = New(l);

        Node *program = ParseProgram(p);

        checkParserErrors(p);

        if(!TestLetStatement(program->Statements_program[0], expected_identifier[i]))
        {
            std::cout << "testletstatement failed \n";
        }
        if(!testLiteralExpression(program->Statements_program[0]->Value_identifier, expected_value[i]))
        {
            std::cout << "testliteralexpression faield\n";
        }



    }
}

/*
int main()
{
  TestNextToken();
}
*/