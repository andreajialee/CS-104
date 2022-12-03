// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "PrintallStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "GotoStatement.h"
#include "IfStatement.h"
#include "GosubStatement.h"
#include "ReturnStatement.h"
#include "ProgramState.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	string var;
	string num;
	string op;
	int val;
	int lineNum;

	ss << line;
	ss >> lineNum;
	ss >> type;
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
	if(type == "PRINT"){
		ss >> var;
		statement = new PrintStatement(var);
	}
	if(type == "PRINTALL"){
		statement = new PrintallStatement();
	}
	if(type == "ADD"){
		ss >> var;
		ss >> num;
		statement = new AddStatement(var,num);
	}
	if(type == "SUB"){
		ss >> var;
		ss >> num;
		statement = new SubStatement(var,num);
	}
	if(type == "MULT"){
		ss >> var;
		ss >> num;
		statement = new MultStatement(var,num);
	}
	if(type == "DIV"){
		ss >> var;
		ss >> num;
		statement = new DivStatement(var,num);
	}
	if(type == "GOTO"){
		ss >> val;
		statement = new GotoStatement(val);
	}
	if(type == "IF"){
		ss >> var;
		ss >> op;
		ss >> val;
		ss >> type;
		ss >> lineNum;
		statement = new IfStatement(var,op,val,lineNum);
	}
	if(type == "GOSUB"){
		ss >> lineNum;
		statement = new GosubStatement(lineNum);
	}
	if(type == "RETURN"){
		statement = new ReturnStatement();
	}
	if(type == "END" || type == "."){
		return NULL;
	}

	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );

	ProgramState state = ProgramState(program.size());
	while(program[state.returnCounter()]!=NULL){
		program[state.returnCounter()]->execute(&state,outf);
	}
}
