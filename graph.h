/**
 * @file graph.h Prototype of class functions.
 *
 * @brief
 *            Prototyping Graph class member 
 * functions and nested class Vertex and Neighbor.
 *
 * @author Athit Vue
 * @date 5/02/2016
 */
#ifndef GRAPH_H
#define GRAPH_H


#include <map>
#include <string>
#include <algorithm>
#include "minpriority.h"

using std::map;
using std::string;

class Graph
{
  public:
    void addVertex(string name);
    void addEdge(string from, string to, int weight);
    string getShortestPath(string from, string to);
  private:
    class Vertex
    {
      public:
        string pi;
        int key;
    };
    class Neighbor
    {
      public:
        string name;
        int weight;
        //overloading < operater to use std::sort.
        inline bool operator < (const Neighbor &i)
        {return ( name < i.name);}
    };
    
    vector<Neighbor> neighbors;
    MinPriorityQ minQ;
    string currentSource;
    map<string, Vertex> vertices;
    map<string, vector<Neighbor>> adjList;
    void buildSSPTree(string source);
    void relax(string u, string v, int weight);
};

#endif //GRAPH_H
    