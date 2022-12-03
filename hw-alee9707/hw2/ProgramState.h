// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED
#include <map>
#include <stack>
#include <string>
#include <cstdlib>
#include <iostream>

class ProgramState
{
public:
	ProgramState(int numLines);
	void incrementCounter();
	void equal(std::string s, int n);
	int returnVal(std::string s);
	bool checkNum(std::string s);
	int returnCounter();
	void setCounter(int n);
	void addLine(int n);
	int getLine();
	void removeLine();
	std::map<std::string,int> returnMap();

	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.


private:
	int m_numLines;
	int counter;
	std::map<std::string, int> vars;
	/* You will need to use a Stack to handle GOSUB and RETURN statements.
	Whenever you reach a GOSUB statement, you should push the line number
	you want to return to onto your stack. When you reach a RETURN statement,
	you should pop the line number from your stack and jump to that line.
	If you hit a RETURN statement and nothing is on your stack, the program
	 should terminate as if it hit an END statement. */
	std::stack<int> lines;
};

#endif
