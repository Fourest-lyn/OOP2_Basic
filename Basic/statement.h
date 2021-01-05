/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <utility>

#include "evalstate.h"
#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};

//This class use for throw and judge the goto what line.
class Goto
{
    int line_number;
public:
    explicit Goto(int x):line_number(x){}
    int getNum() const{return line_number;}
};

//This class use for throw and means the end of the program.
class End{};

class Error{};

//Done
class rem_ : public Statement
{
    std::string comment;

public:
    explicit rem_(std::string str):comment(std::move(str)){}
    void execute(EvalState & state) override {}
};

//Done
class let_ : public Statement
{
    Expression *exp;

public:
    explicit let_(Expression *);
    void execute(EvalState & state) override;
    ~let_() override { delete exp; }

};

//Todo
class pri_ : public Statement
{
    Expression *exp;

public:
    explicit pri_(Expression *);
    void execute(EvalState & state) override;
    ~pri_() override { delete exp; }

};

//Todo
class inp_ : public Statement
{
    std::string name;

public:
    explicit inp_(std::string str):name(std::move(str)){}
    void execute(EvalState & state) override;

};

//Done
class end_ : public Statement
{
public:
    void execute(EvalState & state) override{throw End();}
};

//Done
class got_ : public Statement
{
    int n;

public:
    explicit got_(int n_):n(n_){}
    void execute(EvalState & state) override;
};

//Todo
class ife_ : public Statement
{
    Expression *lhs,*rhs;
    std::string cmp;
    int n;

public:
    ife_(Expression *l,const std::string &c,Expression *r,int position);
    void execute(EvalState & state) override;
    ~ife_();
};



/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

#endif
