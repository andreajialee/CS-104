// GotoStatement.cpp:
#include "GotoStatement.h"

GotoStatement::GotoStatement(int line)
	: m_line(line)
{}


void GotoStatement::execute(ProgramState * state, std::ostream &outf)
{
	state->setCounter(m_line);
}