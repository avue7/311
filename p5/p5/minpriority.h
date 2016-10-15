/**
 * @file minpriority.h Prototype of class functions.
 *
 * @brief
 *            Prototyping MinPriorityQ class member 
 * functions and nested class Element. 
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
    bool isEmpty();
    bool isMember(string id);
  private:
    class Element
    {
      public:
        Element(string id, int key)
        {this->id = id; this->key = key;}
        string id;
        int key;
    };
    
    vector <Element> minHeap;
    void buildMinHeap();
    void minHeapify(int i);
    int parent(int i);
    int left(int i);
    int right(int i);
};

#endif //MINPRIORITY_H