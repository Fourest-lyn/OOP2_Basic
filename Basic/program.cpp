/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"

using namespace std;

Program::Program()
{
    state=new EvalState;
}

Program::~Program()
{
    delete state;
    auto it=statements.begin();
    while(it!=statements.end())
    {
        delete it->second.x;
        ++it;
    }
    statements.clear();
}

void Program::clear()
{
    delete state;
    state=new EvalState;
    auto it=statements.begin();
    while(it!=statements.end())
    {
        delete it->second.x;
        ++it;
    }
    statements.clear();
}

void Program::addSourceLine(int lineNumber,string line)
{
    /* The "line" input here are all without lineNumber and
     * all with the operations such as "LET" and "GOTO", so on.
     */

    if(statements.find(lineNumber)!=statements.end())
    {
        auto it=statements.find(lineNumber);
        delete it->second.x;
    }

    SourceLine temp;
    temp.source=line;

    TokenScanner scanner(line);
    string temp_str=scanner.nextToken();
    if(temp_str=="LET")
    {
        temp.x=new let_(readE(scanner));
        if(scanner.hasMoreTokens()) throw Error();
    }
    if(temp_str=="PRINT")
    {
        temp.x=new pri_(readE(scanner));
        if(scanner.hasMoreTokens()) throw Error();
    }
    if(temp_str=="INPUT")
    {
        temp.x=new inp_(readT(scanner)->toString());
        if(scanner.hasMoreTokens()) throw Error();
    }
    if(temp_str=="END")
    {
        temp.x=new end_;
        if(scanner.hasMoreTokens()) throw Error();
    }
    if(temp_str=="GOTO")
    {
        temp.x=new got_(readT(scanner)->eval());
    }
//    if(temp_str=="REM") temp.x=new rem_()
    //todo: To input the SourceLine's x;
    statements.insert({lineNumber,temp});
}

//Done;
void Program::removeSourceLine(int lineNumber)
{
    auto it=statements.find(lineNumber);
    if(it==statements.end()) return;

    delete it->second.x;
    statements.erase(it);
}

//Done
string Program::getSourceLine(int lineNumber)
{
    auto it=statements.find(lineNumber);
    if(it==statements.end()) return "";

    //todo: To output a SourceLine.
    return it->second.source;
}

//Done
void Program::setParsedStatement(int lineNumber,Statement *stmt)
{
    auto it=statements.find(lineNumber);
    if(it==statements.end()) throw Error();

    delete it->second.x;
    it->second.x=stmt;

//    if(stmt!=nullptr) delete stmt;
    //Maybe some problem here.
}

//Done
Statement *Program::getParsedStatement(int lineNumber)
{
    auto it=statements.find(lineNumber);
    if(it==statements.end()) return nullptr;

    return it->second.x;
}

//Done
int Program::getFirstLineNumber()
{
    if(statements.empty()) return -1;

    auto it=statements.begin();
    return it->first;
}

//Done
int Program::getNextLineNumber(int lineNumber)
{
    auto it=statements.find(lineNumber);
    ++it;
    if(it==statements.end()) return-1;
    return it->first;
}
