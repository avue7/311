/**
 * @file mstapp.h Prototype of the MSTapp class member functions. 
 *
 * @brief
 *          Prototyping of class member functions that
 *          belong to the MSTapp class. 
 *
 * @author Athit Vue
 * @date 12/5/2016
 */
#ifndef __MSTAPP_H
#define __MSTAPP_H

#include <iostream>
#include <string>
#include <cctype>
#include "minpriority.h"
#include "graph.h"

using namespace std;

int main();

class MSTapp 
{
  public:
    void readGraph();
  private:
    Graph myGraph;
};

#endif