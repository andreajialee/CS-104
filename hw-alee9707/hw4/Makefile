CXX = g++
CXXFLAGS = -g -Wall -std=c++11 

rsa: rsa.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 
rsa.o: rsa.cpp  
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c rsa.cpp

clean:
	rm -f *.o rsa