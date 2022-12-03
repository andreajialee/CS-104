// MultStatement.cpp:
#include "MultStatement.h"

MultStatement::MultStatement(std::string variableName, std::string val)
	: m_variableName( variableName ), m_value(val)
{}


void MultStatement::execute(ProgramState * state, std::ostream &outf)
{
	int num = state->returnVal(m_variableName);
	if(state->checkNum(m_value)){
		num *= stoi(m_value);
		state->equal(m_variableName, num);
	}
	else{
		int num2 = state->returnVal(m_value);
		num *= num2;
		state->equal(m_variableName, num);
	}
	state->incrementCounter();
}