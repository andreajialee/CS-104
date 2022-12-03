// IfStatement.cpp:
#include "IfStatement.h"

IfStatement::IfStatement(std::string variableName, std::string op, int val, int line)
	: m_variableName( variableName ), m_op( op), m_value(val), m_line(line)
{}



void IfStatement::execute(ProgramState * state, std::ostream &outf)
{
	int num = state->returnVal(m_variableName);
	if(m_op == "<"){
		if(num<m_value){
			state->setCounter(m_line);
		}
	}
	else if(m_op == "<="){
		if(num<=m_value){
			state->setCounter(m_line);
		}		
	}
	else if(m_op == ">"){
		if(num>m_value){
			state->setCounter(m_line);
		}		
	}
	else if(m_op == ">="){
		if(num>=m_value){
			state->setCounter(m_line);
		}		
	}
	else if(m_op == "="){
		if(num==m_value){
			state->setCounter(m_line);
		}		
	}
	else{
		if(num!=m_value){
			state->setCounter(m_line);
		}
	}
	state->incrementCounter();
}