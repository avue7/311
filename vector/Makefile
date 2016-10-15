CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

vector: vector.o
	$(CXX) -o vector vector.o

vector.o: vector.cpp vector.h

clean:
	rm -f *.o vector 
