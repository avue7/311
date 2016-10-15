/**
 * @file sspapp.h Prototype of class SSPapp functions.
 *
 * @brief
 *            Prototyping SSPapp class member functions
 * and instiantiate a class object mygraph of class
 * Graph. 
 *
 * @author Athit Vue
 * @date 5/02/2016
 */
#ifndef SSPAPP_H
#define SSPAPP_H

#include "graph.h"

class SSPapp 
{
  public:
    void readGraph();
    void processQueries();
  private:
    Graph myGraph;   
};

#endif //SSPAPP_H