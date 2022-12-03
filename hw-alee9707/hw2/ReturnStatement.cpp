// ReturnStatement.cpp:
#include "ReturnStatement.h"

ReturnStatement::ReturnStatement()
{}

void ReturnStatement::execute(ProgramState * state, std::ostream &outf)
{
    int lineNum = state->getLine();
    state->removeLine();
    state->setCounter(lineNum);
}
