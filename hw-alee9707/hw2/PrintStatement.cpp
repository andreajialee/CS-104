// PrintStatement.cpp:
#include "PrintStatement.h"

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	outf << std::to_string(state->returnVal(m_variableName)) << std::endl;
	state->incrementCounter();
}
