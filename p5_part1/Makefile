CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

minpriority: minpriority.o main.o
	$(CXX) -o minpriority minpriority.o main.o

minpriority.o: minpriority.cpp minpriority.h

main.o: main.cpp minpriority.o

clean:
	rm -f *.o minpriority main
