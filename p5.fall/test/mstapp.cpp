/**
 * @file mstapp.cpp Functions of class MSTapp. 
 *
 * @brief
 *          Implementation of class member functions that
 *          belongs to the MSTapp class. 
 *
 * @author Athit Vue
 * @date 12/5/2016
 */
#include "mstapp.h"

int main()
{
  MSTapp first_app;  // Instintiate an object from MSTapp class.
  first_app.readGraph(); // Read the graph.
  return 0;
}

/**
 * MSTapp::readGraph
 * 
 * This public member function of the MSTapp class will read 
 * a weighted undirected graph from standard input and write 
 * the structure of the MST to standard output. The writing to 
 * standard output will actually happen in graph.cpp for easiness.
 * The specified input will consist of a set of vertex identifiers on 
 * the first line, separated by spaces. The next line will be followed
 * by two vertex identifiers and a numberical weight. We are 
 * assuming that the input will not deviate from this format. 
 */
void MSTapp::readGraph()
{
  /* Declaring variables needed for graph here*/
  string vertex;
  string temp;
  string u;
  string v;
  string source;
  
  int weight;
  weight = 0; // Initialize weight to 0.
  
  getline(cin,vertex); // Get the vertex identifiers using a single string. 

  /* Lets separate the vertex by delimiter space and add them
   * to the vertices map defined in the graph class.
   */
  for (int i = 0; vertex[i] != '\0'; i++)
  {
    // If we find a space, it is a delimiter. Move to next.
    if(vertex[i] == ' ')
    {
      continue;
    }
    temp = vertex[i];
    myGraph.addVertex(temp); // Add the temp vertex to vertices map.
  }
  
  /* Get the edge for the starting vertex
   * which is the second line of the standard input.
   */
  cin >> u >> v >> weight;
  /* Store the edge in the adjList map */
  myGraph.addEdge(u, v, weight);
  
  source = u; // Initialize the start vertex to u
  
  /* Now that we've got the starting vertex, let's look to see if 
   * there are other edges in the input file and add it to the
   * adjList map. We know there are no more edges when we
   * have reach the EOF.
   */
  while(cin.peek()!=EOF)
  {
    cin >> u >> v >> weight;
    myGraph.addEdge(u, v, weight);
  }
  
  /* Lets go ahead and run the program to get the structure of the
   * graph to be outputted to standard output. Remember to include
   * the total weight of the graph. RUN MST NOW!
   */
  myGraph.mst(source);
} 