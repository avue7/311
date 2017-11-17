#include <iostream>
#include <string>
#include "rbapp.h"

using namespace std;

int main()
{
  RBapp go;

  go.mainLoop();
  return 0;
}    

//connection between main and RBapp
void RBapp::mainLoop()
{
  while(!cin.eof())
  {
    processCommand();
  }
}

//process all commands
void RBapp::processCommand()
{ 
  string key, command;
  
  cin>>command;
        
  if(command == "print")
  {
    processPrint();
  }
    
  else if(command == "insert")
  {
    cin>>key;
    processInsert(key);
  }
  else if(command == "find")
  {
    cin>>key;
    processFind(key);   
  }
  else if(command == "quit")
  {
    processQuit();
  }
  else if(command == "delete")
  {
    cin>>key;
    processDelete(key);
  }
}

//calls print function in rbtree
void RBapp::processPrint()
{
  myRBT.rbPrintTree();
}

//inserts key and data into tree
void RBapp::processInsert(string& key)
{
  string data;
  
  getline(cin,data);
  myRBT.rbInsert(key, data);
}

//finds nodes with matching keys and prints out key and data
void RBapp::processFind(string& key)
{
  vector<const string*> inputVector = myRBT.rbFind(key);

  for (unsigned int i=0; i < inputVector.size(); i++)
  {
    cout << key << *inputVector[i] << endl;
  }
}

//finds nodes with matching keys and data and deletes them
void RBapp::processDelete(string& key) {
  string data;
  
  getline(cin,data);
  myRBT.rbDelete(key, data);
}

//quits
void RBapp::processQuit() {
  return;
}