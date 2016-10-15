CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

sspapp: sspapp.o graph.o minpriority.o 
	$(CXX) -o sspapp minpriority.o graph.o sspapp.o

minpriority.o: minpriority.cpp minpriority.h

graph.o: graph.cpp graph.h

sspapp.o: sspapp.cpp sspapp.h

clean:
	rm -f *.o minpriority graph sspapp
