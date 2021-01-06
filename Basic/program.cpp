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
//#include "statement.h"

using namespace std;

Program::Program()
{
    state=new EvalState;
}

Program::~Program()
{
    auto it=statements.begin();
    while(it!=statements.end())
    {
        delete it->second.x;
        ++it;
    }
    statements.clear();
    delete state;
}

void Program::clear()
{
    auto it=statements.begin();
    while(it!=statements.end())
    {
        delete it->second.x;
        ++it;
    }
    statements.clear();
    delete state;
    state=new EvalState;
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
        statements.erase(it);
    }

    SourceLine temp;
    temp.source=line;

    TokenScanner scanner(line);
    scanner.ignoreWhitespace();
    scanner.nextToken();
    string temp_str=scanner.nextToken();

    if(temp_str=="REM")
    {
        temp.x=new rem_;
        statements.insert({lineNumber,temp});
        return;
    }
    if(temp_str=="LET") temp.x=new let_(readE(scanner));
    if(temp_str=="PRINT") temp.x=new pri_(readE(scanner));
    if(temp_str=="INPUT") temp.x=new inp_(readT(scanner)->toString());
    if(temp_str=="END") temp.x=new end_;
    if(temp_str=="GOTO")
    {
        temp.x=new got_(readT(scanner)->eval(*state));
    }
    if(temp_str=="IF")
    {
        string left,right;
        int mid=0;
        string cmp;
        for(int i=0;i<line.length();++i)
        {
            if(line[i]=='>' || line[i]=='<' || line[i]=='=')
            {
                mid=i;
                cmp=line[i];
                left=line;
                left.erase(i);
                right=line.substr(i+1);
                break;
            }
        }
        scanner.setInput(left);
        scanner.nextToken();
        scanner.nextToken();
        Expression *l=readE(scanner);

        scanner.setInput(right);
        Expression *r=readE(scanner);
//        cout<<"##"<<left<<"##"<<right<<"##"<<r->eval(*state)<<endl;
//        cout<<"##"<<scanner.nextToken()<<"##"<<cmp<<"##"<<endl;
        if(scanner.nextToken()!="THEN") throw Error();

        int position=readT(scanner)->eval(*state);
        temp.x=new ife_(l,cmp,r,position);
    }
    //Check if there are nothing left.

//    if(scanner.hasMoreTokens()) cout<<"##"<<temp_str<<"##"<<line<<"##"<<endl;
    if(scanner.hasMoreTokens()) throw Error();

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

void Program::RunAllRecords()
{
    if(statements.empty()) return;
    auto it=statements.begin();
    while(it!=statements.end())
    {
        try
        {
            it->second.x->execute(*state);
            ++it;
        }
        catch (End) { return; }
        catch (Goto temp)
        {
            int x=temp.getNum();
            it=statements.find(x);
            if(it==statements.end()) error("LINE NUMBER ERROR");
        }
    }

}

void Program::DisplayAllRecords()
{
    if(statements.empty()) return;
    auto it=statements.begin();
    while(it!=statements.end())
    {
        cout<<it->second.source<<endl;
        ++it;
    }
}



















