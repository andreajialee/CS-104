#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <iostream>

class DivStatement: public Statement
{
private:
	std::string m_variableName;
    std::string m_value;
	
public:
	DivStatement(std::string variableName, std::string val);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
