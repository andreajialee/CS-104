#include "ProgramState.h"

ProgramState::ProgramState(int numLines){
    m_numLines = numLines;
    counter = 1;
}

void ProgramState::incrementCounter(){
    counter++;
}

void ProgramState::equal(std::string s, int n){
    vars[s] = n;
}

int ProgramState::returnVal(std::string s){
    std::map<std::string,int>::iterator it = vars.end();
    if(vars.find(s)==it){
        vars[s] = 0;
    }
    return vars[s];
}

bool ProgramState::checkNum(std::string s){
    for(int i=0; i<s.length(); i++){
        if (std::isdigit(s[i]) == 0) return false;
    }
    return true;
}

int ProgramState::returnCounter(){
    return counter;
}

void ProgramState::setCounter(int n){
    counter = n;
}

void ProgramState::addLine(int n){
    lines.push(n);
}
int ProgramState::getLine(){
    return lines.top();
}
void ProgramState::removeLine(){
    lines.pop();
}
std::map<std::string,int> ProgramState::returnMap(){
    return vars;
}