/**
 * @file minpriority.h Prototype of class functions.
 *
 * @brief
 *            Prototyping MinPriorityQ class member functions
 *  and nested class Element. 
 *
 * @author Athit Vue
 * @date 5/02/2016
 */
#ifndef MINPRIORITY_H
#define MINPRIORITY_H

#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

class MinPriorityQ
{
  public:
    MinPriorityQ(/*int size*/);
    ~MinPriorityQ();
    void insert(string id, int key);
    void decreaseKey(string id, int newKey);
    string extractMin();
    bool isMember(string id);
    //int getVectorSize(); **for testing purposes
    //void print();  **for testing purposes
  private:
    class Element
    {
      public:
        string id;
        int key;
        Element(string i, int k);
        ~Element();
    };
    vector <Element> minHeap;
    void buildMinHeap();
    void minHeapify(int i);
    int parent(int i);
    int left(int i);
    int right(int i);
};

#endif //MINPRIORITY_H