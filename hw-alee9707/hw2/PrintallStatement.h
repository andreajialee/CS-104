#ifndef PRINTALL_STATEMENT_INCLUDED
#define PRINTALL_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class PrintallStatement: public Statement
{
private:
	
public:
	PrintallStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif