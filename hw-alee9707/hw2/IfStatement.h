#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <iostream>

class IfStatement: public Statement
{
private:
    std::string m_variableName;
    std::string m_op;
    int m_value;
    int m_line;
	
public:
	IfStatement(std::string variableName, std::string op, int val, int line);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
