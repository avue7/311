/**
 * @file rbapp.cpp
 *
 * @brief
 *          Contains main and also the member functions 
 *          for the RBapp class.
 *
 * @author Athit Vue
 * @date 04/16/2016
 */
#include <iostream>
#include <string>
#include "rbapp.h"

using namespace std;

/**
 * RBapp constructor
 */
RBapp::RBapp()
{
  done = false;
}
 
 /**
 * int main
 *
 * Instantiates RBapp class and calls the 
 * mainLoop function.
 */
int main()
{
  RBapp first_one;
  first_one.mainLoop();
  return 0;
}    

/**
 * RBapp::mainLoop
 * 
 * This contains the main while loop of the program.
 * It keeps calling function processCommand until
 * the command is quit. Boolean variable done is 
 * intialized as false and loop terminates when done
 * becomes true after function processQuit is called. 
 */
void RBapp::mainLoop()
{
  //While eof is not reached, execute statement. Else
  //return to main(), even if quit command was not 
  //recieved. 
  while(!cin.eof())
  {
    if (done == false)
    {
      processCommand();
    }
    else
    {
      break;
    }
  }
  return;
}

/**
 * RBapp::processCommand
 * 
 * This function calls the approriate private functions based
 * on the inputted command. 
 */
void RBapp::processCommand()
{ 
  string key, command;
  
  cin>>command;
        
  if(command == "print")
  {
    processPrint();
  }
  else if(command == "delete")
  {
    cin>>key;
    processDelete(key);
  }
  else if(command == "find")
  {
    cin>>key;
    processFind(key);   
  }
  else if(command == "insert")
  {
    cin>>key;
    processInsert(key);
  }
  else if(command == "quit")
  {
    processQuit();
  }
}

/**
 * RBapp::processInsert
 * 
 * This is a private function of the RBapp class.
 * This is the function that inserts the key and the value 
 * that belongs to the key into the red-black tree.
 *
 * @param key The key identifier. 
 */
void RBapp::processInsert(string& key)
{
  string data;
  cin.ignore();
  getline(cin, data);
  myRBT.rbInsert(key, data);
}

/**
 * RBapp::processPrint
 *
 * This private function from the RBapp class calls the member 
 * function from the RBTree class to print the tree.
 */
void RBapp::processPrint()
{
  myRBT.rbPrintTree();
}

/**
 * RBapp::processDelete
 * 
 * This private function calls the delete function from the
 * RBTree class to delete the Node that the user wants to 
 * delete. 
 * 
 * @param key    The key identifier to the node that the user
 *                        wants to delete.
 */
void RBapp::processDelete(string& key) {
  string data;
  cin.ignore();
  getline(cin,data);
  myRBT.rbDelete(key, data);
}

/**
 * RBapp::processFind
 *
 * This private function calls the member function rbFind with 
 * vector datatype to find a node with matching key and prints
 * both the key and the satellite data.
 * 
 * @param key The key identifier of the node we want to find.
 */
void RBapp::processFind(string& key)
{
  vector<const string*> inputVector = myRBT.rbFind(key);

  for (unsigned int i=0; i < inputVector.size(); i++)
  {
    cout << key << " " << *inputVector[i] << endl;
  }
}


/**
 * RBapp::processQuit
 *
 * This private function of the RBapp class basically just 
 * sets the boolean variable done to true for helping in 
 * termination of the while loop in the public function 
 * mainLoop.
 */
void RBapp::processQuit() 
{
  done = true;
  return;
}