CXX = g++
CXXFLAGS = -g -Wall -std=c++11

scheduling: scheduling.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 
scheduling.o: scheduling.cpp  
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c scheduling.cpp

clean:
	rm -f *.o scheduling