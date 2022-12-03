CXX=g++
CXXFLAGS=-g -Wall

OBJS = ProgramState.o LetStatement.o PrintStatement.o PrintallStatement.o AddStatement.o SubStatement.o MultStatement.o DivStatement.o GotoStatement.o IfStatement.o GosubStatement.o ReturnStatement.o

interpreter: interpreter.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ -c interpreter.cpp

ProgramState.o: ProgramState.cpp ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c ProgramState.cpp

LetStatement.o: LetStatement.cpp LetStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c LetStatement.cpp

PrintStatement.o: PrintStatement.cpp PrintStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c PrintStatement.cpp

PrintallStatement.o: PrintallStatement.cpp PrintallStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c PrintallStatement.cpp

AddStatement.o: AddStatement.cpp AddStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c AddStatement.cpp

SubStatement.o: SubStatement.cpp SubStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c SubStatement.cpp

MultStatement.o: MultStatement.cpp MultStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c MultStatement.cpp

DivStatement.o: DivStatement.cpp DivStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c DivStatement.cpp

GotoStatement.o: GotoStatement.cpp GotoStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c GotoStatement.cpp

IfStatement.o: IfStatement.cpp IfStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c IfStatement.cpp

GosubStatement.o: GosubStatement.cpp GosubStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c GosubStatement.cpp

ReturnStatement.o: ReturnStatement.cpp ReturnStatement.h Statement.h ProgramState.h
	$(CXX) $(CXXFLAGS)  -o $@ -c ReturnStatement.cpp

clean:
	rm -f *.o interpreter