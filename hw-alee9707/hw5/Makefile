CXX = g++
CXXFLAGS = -g -Wall --std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

Hashtable.o: Hashtable.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Hashtable.cpp

clean:
	rm -f *.o hashtable