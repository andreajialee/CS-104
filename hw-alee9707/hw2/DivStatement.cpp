// DivStatement.cpp:
#include "DivStatement.h"

DivStatement::DivStatement(std::string variableName, std::string val)
	: m_variableName( variableName ), m_value(val)
{}


void DivStatement::execute(ProgramState * state, std::ostream &outf)
{
	int num = state->returnVal(m_variableName);
	if(state->checkNum(m_value)){
		if(stoi(m_value) == 0){
			outf << "Divide by zero exception" << std::endl;
			state->incrementCounter();
			return;
		}
		num/= stoi(m_value);
		state->equal(m_variableName, num);
	}
	else{
		int num2 = state->returnVal(m_value);
		num /= num2;
		state->equal(m_variableName, num);
	}
	state->incrementCounter();
}
