/**
 * @file minpriority.h Implementation of class 
 *                               member functions. 
 *
 * @brief
 *            Implementation of class functions that
 * belongs to the Graph class. 
 *
 * @author Athit Vue
 * @date 5/02/2016
 */

#include "graph.h"

/***************************
 *--Public Functions Below--*
***************************/
/**
 * Graph::addVertex
 * 
 * Creates a temp vertex object and initializes the 
 * vertex's parent to NIL. Key of vertex is initialized
 * to 200 to represent infinity. Then vertex is added
 * into the vertices map with the vertices name as 
 * the key. 
 * 
 * @param name The key of vertex inside the vertices
 *                         map.
 */
void Graph::addVertex(string name)
{  
  Vertex add_vertex; 
  add_vertex.pi = "NIL"; //Initialize parent to NIL
  add_vertex.key = 200;

  vertices[name] = add_vertex;
}

/**
 * Graph::addEdge
 * 
 * This public function adds in the edge of the 
 * vertices. It keeps track of the vertices neighbors
 * and the weight it carries.
 *
 * @param from The vertex from where we start.
 * @param to The vertex to where we want to go.
 * @param weight The weight of the neighbor. 
 */
void Graph::addEdge(string from, string to, int weight)
{
  //Instintiate a Neighbor class v to store the name 
  //and weight.
  Neighbor v;
  v.name = to;
  v.weight = weight;
  
  neighbors.push_back(v);
  //Add adjacent neighbors. From (u) -> (v (weight))
  adjList[from].push_back(v);
  
  //Sort the vector Neighbor in the map by name in 
  //ascending order.
  map<string, vector<Neighbor>>::iterator it;
  for( it = adjList.begin(); it != adjList.end(); it++)
  {
    sort(it->second.begin(), it->second.end());
  }
}

/**
 * Graph::getShortestPath
 * 
 * This is a public function to handle the quieries.
 * This funtion will return the results from getting
 * the shortest path. It first call buildSSPTree to 
 * create a tree.
 * 
 * @param from The vertex we want to start from.
 * @param to The vertex we want to go to.
 * @return string We are returning a string to be 
 *                          outputted by the caller. 
 */
string Graph::getShortestPath(string from, string to)
{
  //Build a tree first.
  buildSSPTree(from);
  
  //Return this string for printout.
  int distance = vertices[to].key;
  string shortest_path;
  string cur_name = to;
  while(cur_name != "NIL")
  {
    shortest_path = cur_name + "->" + shortest_path;
    cur_name = vertices[cur_name].pi;
  }
  shortest_path = shortest_path.substr(0, 
  shortest_path.size() - 2);
  return shortest_path + " with length " + 
              std::to_string(distance);
}

/****************************
 *--Private Functions Below--*
****************************/
/**
 * Graph::buildSSPTree
 * 
 * This is a private function to Graph class to build
 * a single shortest path tree. 
 *
 * @param source  The source in which we want to 
 *                            start from.
 */
void Graph::buildSSPTree(string source)
{
  //Initializing all vertices.
  map<string, Vertex>::iterator it;
  for (it = vertices.begin(); it != vertices.end(); it++)
  {
    Vertex &temp = it->second;
    temp.pi = "NIL";
    temp.key = 200;
  }
  
  vertices[source].key = 0; //Set source key to 0.

  //Put source in minQ first.
  minQ.insert(source, vertices[source].key);
  
  //Need to add all other vertices to minQ except source.
  for (it = vertices.begin(); it != vertices.end(); it++)
  {
    if (it->first == source)
    {
      continue;
    }
    minQ.insert(it->first, it->second.key);
  }
  //While minQ not empty check its neighbors.
  while (!minQ.isEmpty())
  {
    currentSource = minQ.extractMin();
    vector<Neighbor>neighbors = adjList[currentSource];

    for(unsigned int i=0; i < neighbors.size(); i++)
    {
      relax(currentSource, neighbors[i].name, 
      neighbors[i].weight );
    }
  }
}

/**
 * Graph::relax
 *
 * This is a private function that is used by 
 * buildSSPTree to check the weight of each of the 
 * neighbors that belong to each vertices in the 
 * minQ. If the current path has a lower weight then
 * use it instead. Record the path it took and call
 * decreaseKey to update the vertices.
 *
 * @param u The source.
 * @param v The vertex to.
 * @param weight The weight of the neighbors.
 */
void Graph::relax(string u, string v, int weight)
{
    if (vertices[v].key > vertices[u].key + weight)
    {
      vertices[v].key = vertices[u].key + weight;
      vertices[v].pi = u;
      
      minQ.decreaseKey(v, vertices[v].key);
    }
}