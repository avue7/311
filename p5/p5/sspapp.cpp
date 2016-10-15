/**
 * @file sspapp.cpp 
 *
 * @brief
 *            Implementation of class member functions
 * and int main(). 
 *
 * @author Athit Vue
 * @date 5/02/2016
 */
#include "sspapp.h"
using std::cout;
using std::endl;
using std::cin;

/**
 * SSPapp::processQueries
 *
 * This function will process the queries to get the 
 * shortest path of the vertices from and to. It will
 * also display the query results to standard output.
 */
void SSPapp::processQueries()
{
  string from, to;
  while (cin >> from || !std::cin.eof())
  { 
    cin >> to;
    cout << myGraph.getShortestPath(from, to) 
    << endl;
  }
}

/**
 * SSPapp::readGraph
 *
 * This function will ask the user to input the 
 * number of vertices and the edges. It then ask 
 * the user to input the from and to vertices and the
 * weight. It will call processQueries to handle the 
 * queries.
 */
void SSPapp::readGraph()
{
  int numb_vertices = 0;
  cin >> numb_vertices;

  string identifier;

  while (numb_vertices != 0)
  {
    cin >> identifier;
    myGraph.addVertex(identifier);
    numb_vertices--;
  }
  
  //Add edges...
  int numb_edges = 0;
  cin >> numb_edges;
  string from, to;
  int weight = 0;
  
  while (numb_edges != 0)
  {
    cin >> from;
    cin >> to;
    cin >> weight;
    myGraph.addEdge(from, to, weight);
    numb_edges--;
  }
  
  processQueries();
}

/*main(): Instantiate a class object app an call 
               function readGraph() to ask user for input.
*/
int main()
{
  SSPapp app;
  app.readGraph();
  return 0;
}