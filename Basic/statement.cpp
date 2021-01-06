/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include <iostream>
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

void let_::execute(EvalState &state)
{
    exp->eval(state);
}

let_::let_(Expression *input)
{
    exp=input;
}

void pri_::execute(EvalState &state)
{
    cout<<exp->eval(state)<<endl;
}

pri_::pri_(Expression *input)
{
    exp=input;
}

void inp_::execute(EvalState &state)
{
    cout<<" ? ";
    string temp;
    getline(cin,temp);
    int value=0;
    for(int i=0;i<temp.length();++i)
    {
        if(temp[i]>'9' || temp[i]<'0') error("INVALID NUMBER");
        value=value*10+int(temp[i]-'0');
    }

    state.setValue(name,value);
}

void got_::execute(EvalState &state)
{
    throw Goto(n);
}

void ife_::execute(EvalState &state)
{
    int l=lhs->eval(state);
    int r=rhs->eval(state);
    bool If_correct=true;
    if(cmp=="=") If_correct=(l==r);
    if(cmp==">") If_correct=(l>r);
    if(cmp=="<") If_correct=(l<r);
    if(If_correct) throw Goto(n);
}

ife_::ife_(Expression *l,const string &c,Expression *r,int position)
{
    cmp=c;
    lhs=l;
    rhs=r;
    n=position;
}

ife_::~ife_()
{
    delete lhs;
    delete rhs;
}


















