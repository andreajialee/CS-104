#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <iostream>

class SubStatement: public Statement
{
private:
	std::string m_variableName;
    std::string m_value;
	
public:
	SubStatement(std::string variableName, std::string val);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
