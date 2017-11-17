/**
 * @file graph.h Prototype of class Graph functions. 
 *
 * @brief
 *          Prototyping of class member functions that
 *          belongs to the Graph class. Private nested 
 *          class Vertex and Neighbor's member variables
 *          are also declared here. 
 *
 * @author Athit Vue
 * @date 12/5/2016
 */
#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "minpriority.h"

using namespace std;

class Graph 
{
  public:
    Graph(){} // Default constructor 
    ~Graph(){} // Empty default destructor
    void addVertex (string name);
    void addEdge (string from, string to, int weight);
    void mst(string start);
      
  private:
    class Vertex
    {
      public:
        string pi;
        int key;
        Vertex(){}
    };

    class Neighbor
    {
      public:
        string name;
        int weight;
        Neighbor(){}
        // Sort the neighbors by overloading operator < 
        bool operator < (const Neighbor &i) const {return ( name < i.name);}
    };

  MinPriorityQ *minQ;
  
  vector<Neighbor> neighbors; // Needed this for sorting the neighbors
  map<string, Vertex> vertices;
  map<string, vector<Neighbor>> adjList;
    

};

#endif