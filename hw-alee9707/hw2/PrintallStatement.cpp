// PrintallStatement.cpp:
#include "PrintallStatement.h"

PrintallStatement::PrintallStatement()
{}


void PrintallStatement::execute(ProgramState * state, std::ostream &outf)
{
    std::map<std::string,int> temp = state->returnMap();
    std::map<std::string,int>::iterator it;
    for(it=temp.begin(); it!=temp.end(); it++){
        outf << (*it).first << " " << (*it).second << std::endl;
    }
    state->incrementCounter();
}