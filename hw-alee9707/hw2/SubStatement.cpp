// SubStatement.cpp:
#include "SubStatement.h"

SubStatement::SubStatement(std::string variableName, std::string val)
	: m_variableName( variableName ), m_value(val)
{}


void SubStatement::execute(ProgramState * state, std::ostream &outf)
{
	int num = state->returnVal(m_variableName);
	state->equal(m_variableName,0);
	if(state->checkNum(m_value)){
		num -= stoi(m_value);
		state->equal(m_variableName, num);
	}
	else{
		int num2 = state->returnVal(m_value);
		num -= num2;
		state->equal(m_variableName, num);
	}
	state->incrementCounter();
}