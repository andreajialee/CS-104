#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <iostream>

class GosubStatement: public Statement
{
private:
	int m_line;
	
public:
	GosubStatement(int line);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
