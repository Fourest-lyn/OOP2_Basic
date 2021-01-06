/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"

#include "../StanfordCPPLib/map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
   /* Empty */
}

EvalState::~EvalState() {
   /* Empty */
}

void EvalState::setValue(string var, int value) {
    bool flag=false;
    if(var=="LET" || var=="IF" || var=="THEN" || var=="PRINT") flag=true;
    if(var=="INPUT" || var=="REM" || var=="END" || var=="GOTO") flag=true;
    if(var=="RUN" || var=="LIST" || var=="CLEAR" || var=="QUIT") flag=true;
    if(var=="HELP") flag=true;
    if(flag) error("SYNTAX ERROR");
   symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
   return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
   return symbolTable.containsKey(var);
}
