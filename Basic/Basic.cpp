/*
 * File: Basic.cpp
 * ---------------
 * Name: Fourest
 * Section: Null
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
//#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
//#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main()
{
//   EvalState state;
   Program program;
//   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try
      {
         processLine(getLine(), program, *program.state);
      }
      catch (ErrorException & ex)
      {
         cout<<ex.getMessage()<<endl;
      }
   }
   return 0;
}

int StringToInt(string temp)
{
    int output=0;
    for(int i=0;i<temp.length();++i)
    {
        if(temp[i]>'9' || temp[i]<'0') throw Error();
        output=output*10+int(temp[i]-'0');
    }
    return output;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state)
{
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    string temp=scanner.nextToken();

    //This IF if used for check if this line should be save in to program.
    if(scanner.getTokenType(temp)==NUMBER)
    {
        int LineNumber=StringToInt(temp);
        if(!scanner.hasMoreTokens())
        {
            program.removeSourceLine(LineNumber);
            return;
        }

        try
        {
            program.addSourceLine(LineNumber,line);
        }
        catch (Error)
        {
            throw ErrorException("SYNTAX ERROR");
        }
    }

    //This judgement is used for check if some source line is
    //legal for input without line number.
    //Done
    if(temp=="REM" || temp=="END" || temp=="GOTO" || temp=="IF")
    {
        throw ErrorException("SYNTAX ERROR");
    }

    if(temp=="LET")
    {
        let_ temp_let(readE(scanner));
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        temp_let.execute(state);
    }
    if(temp=="INPUT")
    {
        inp_ temp_input(readT(scanner)->toString());
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        temp_input.execute(state);
    }
    if(temp=="PRINT")
    {
        pri_ temp_print(readE(scanner));
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        temp_print.execute(state);
    }
    if(temp=="RUN")
    {
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        program.RunAllRecords();
    }
    if(temp=="LIST")
    {
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        program.DisplayAllRecords();
    }
    if(temp=="CLEAR")
    {
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        program.clear();
    }
    if(temp=="QUIT")
    {
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        exit(0);
    }
    if(temp=="HELP")
    {
        if(scanner.hasMoreTokens()) throw ErrorException("SYNTAX ERROR");
        cout<<"This is a simple BASIC interpreter, complete by Fourest.\n";
    }

//    Expression *exp = parseExp(scanner);
//    int value = exp->eval(state);
//    cout << value << endl;
//    delete exp;
}


























