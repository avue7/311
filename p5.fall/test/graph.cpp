/**
 * @file graph.cpp Functions of class Graph. 
 *
 * @brief
 *          Implementation of class member functions that
 *          belongs to the Graph class. 
 *
 * @author Athit Vue
 * @date 12/5/2016
 */
#include "minpriority.h"
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
 * @param name The key of vertex inside the vertices map.
 */
void Graph::addVertex (string name)
{
  Vertex temp_vertex;   
  temp_vertex.pi = "NIL";
  temp_vertex.key = 200;
  vertices[name] = temp_vertex;
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
void Graph::addEdge (string from, string to, int weight)
{
  Neighbor temp_neighbor;
  temp_neighbor.name = to;
  temp_neighbor.weight = weight;
  
  // Add the vertex to the neighbors vector for sorting.
  //neighbors.push_back(temp_neighbor);
  adjList[from].push_back(temp_neighbor); 

  temp_neighbor.name = from;
  adjList[to].push_back(temp_neighbor);
  
  /* Sort the vector Neighbor in the map by name in ascending order. */
  /*map<string, vector<Neighbor>>::iterator it;
  for( it = adjList.begin(); it != adjList.end(); it++)
  {
    sort(it->second.begin(), it->second.end());
  }*/
}

/**
 * Graph::mst
 * 
 * This is the main function of the program. This is PRIMS MST algorithm.
 * It initializes all vertices and stores them in a minQ. Then it extracts the
 * vertices based on its key value. This function will print to standard 
 * output the vertex identifier, its predecessor's vertex indentifier, and 
 * the weight of its edges. When each minumum path is discovered, 
 * it will update the vertex indentifier accordingly in the minQ. It continues
 * to do this until the minQ is empty. It will then print to standard output
 * the total weight of the MST. 
 *
 * @param start The source of the graph.
 */
void Graph::mst(string start)
{
  /* Note: Initialization for each u subset G.V. happened before this
   * function was called in mstapp.cpp.
   */
  
  int total_weight = 0; // Setting the total weight of MST to 0; 
  
  // Dynamically allocating a new MinQ with size of vertices.
  minQ = new MinPriorityQ(vertices.size());
  
  vertices[start].key = 0; // Source of MST key is 0 (always);

  minQ->insert(start, vertices[start].key);//insert source into the minQ

  /* Add all other initialized vertices into the minQ */
  for(map<string, Vertex>::iterator it = ++vertices.begin(); 
  it != vertices.end(); it++)
  {
    minQ->insert( it->first, it->second.key); //insert the rest into the minQ
  }
  
  string min;
  min = minQ->extractMin(); //find source with weight 0, extract that first.
  
  while(min != "empty") //while there are still things in the queue
  {
    for(unsigned int i = 0; i<adjList[min].size(); i++)
    {
      // Check the adjList for neighbors. If current path to neighbor is 
      // smaller than the weight stored, update the weight. 
      if(vertices[adjList[min][i].name].key > adjList[min][i].weight && 
        minQ->isMember(adjList[min][i].name))
      {
        vertices[adjList[min][i].name].key = adjList[min][i].weight;
        vertices[adjList[min][i].name].pi = min;
        minQ->updateWeight(adjList[min][i].name, adjList[min][i].weight);
      }
    }

    /* Output the vertex identifier, its predecessor's identifier, and the key
     * (weight).
     */
    cout<<min<<" "<<vertices[min].pi<<" "<<vertices[min].key<<endl;
    total_weight = total_weight + vertices[min].key;
    min = minQ->extractMin();
  }
  // When the minQ is empty, then output the total weight of the MST. 
  cout<<total_weight<<endl;
  print();
}

//just a test functon used to see what actually made it into the maps
void Graph::print()
{
    //vertexes
    cout<<"vertex list:"<<endl;
    for(map<string, Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
    {
        cout<<"'"<<it->first<<"' "<<it->second.key<<endl;
    }
    
    //adjacency list
    cout<<endl<<"adjList:"<<endl;
    for(map<string, vector<Neighbor>>::iterator it = adjList.begin(); it != adjList.end(); it++)
    {
        cout<<it->first<<": ";
        for(unsigned int i = 0; i<it->second.size(); i++)
        {
            cout<<it->second[i].name<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}