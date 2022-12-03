// GoSubStatement.cpp:
#include "GosubStatement.h"

GosubStatement::GosubStatement(int line)
	: m_line(line)
{}


void GosubStatement::execute(ProgramState * state, std::ostream &outf)
{
    state->addLine(state->returnCounter()+1);
	state->setCounter(m_line);
}

