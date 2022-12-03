CXX = g++
CXXFLAGS = -g -Wall -std=c++11

doublet: doublet.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 
doublet.o: doublet.cpp  
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c doublet.cpp

clean:
	rm -f *.o doublet