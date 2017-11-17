CC = g++
CFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

mstapp: mstapp.o graph.o minpriority.o
	$(CC) $(LDFLAGS) mstapp.o graph.o minpriority.o -o mstapp

mstapp.o: mstapp.cpp graph.h
	$(CC) $(CFLAGS) mstapp.cpp

graph.o: graph.cpp graph.h minpriority.h
	$(CC) $(CFLAGS) graph.cpp

minpriority.o: minpriority.cpp minpriority.h
	$(CC) $(CFLAGS) minpriority.cpp
    
clean:
	rm *o mstapp
