/**
 * @file minpriority.h Prototype of class MinPriorityQ functions. 
 *
 * @brief
 *          Prototyping of class member functions that
 *          belongs to the MinPriorityQ class. Private nested 
 *          class Element member variables are also declared here.
 *
 * @author Athit Vue
 * @date 12/5/2016
 */
#ifndef __MINPRIORITY_H
#define __MINPRIORITY_H

#include <iostream>
#include <string>

using namespace std;

class MinPriorityQ 
{
  public:
    MinPriorityQ(int size); 
    ~MinPriorityQ(){delete[] minHeap;}
    void insert(string id, int key);
    void decreaseKey(string id, int newKey);
    string extractMin();
    bool isMember(string id);
    
    /* This is an added function to help in updating the 
     * the weight of the vertices that needs to be.
     */
    void updateWeight(string id, int key);

  private:
    class Element
    {
      public:
        string  id;
        int key;
        Element();
    };
   
    Element *minHeap;
    void buildMinHeap();
    void minHeapify(int i);
    int parent(int i);
    int left(int i);
    int right(int i);
    int heap_size; // Keeping track of the minHeap size.
};

#endif