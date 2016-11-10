/**
 * @file rbapp.cpp
 *
 * @brief
 *          Contains main and also the member functions 
 *          for the RBapp class.
 *
 * @author Athit Vue
 * @date 10/31/2016
 */
#include <iostream>
#include "rbapp.h"
#include <string>

using namespace std;

 /**
 * int main
 *
 * Instantiates RBapp class and calls the 
 * mainLoop function.
 */
int main()
{
  RBapp first_app;  
  first_app.mainLoop();
  return 0;
}

/**
 * RBapp::mainLoop
 * 
 * This contains the main while loop of the program.
 * It keeps calling function processCommand until
 * it returns false, or it has eof. 
 */
void RBapp::mainLoop()
{
  string command;
  cin >> command;
  while (!cin.eof())
  {
    bool status_return = processCommand(command);
    if (status_return == true)
    {
      cin >> command;
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
 * 
 * @param command The command inputted from the mainLoop.
 *
 * @return true Return true if command does not equal "quit".
 * @return false Return false if command equals "quit".
 */
bool RBapp::processCommand(string& command)
{
  if (command == "insert")
  {
    string insert_key;
    cin >> insert_key;
    processInsert(insert_key);
    return true;
  }
  else if (command == "find")
  {
    string find_key;
    cin >> find_key;
    processFind(find_key);
    return true;
  }
  else if (command == "delete")
  {
    string delete_key;
    cin >> delete_key;
    processDelete(delete_key);
    return true;
  }
  else if (command == "print")
  {
    processPrint();
    return true;
  }
  else if (command == "quit")
  {
    return false;
  }
  else
  {
    return true; //Return true if invalid command.
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
 * RBapp::processDelete
 * 
 * This private function calls the delete function from the
 * RBTree class to delete the Node that the user wants to 
 * delete. 
 * 
 * @param key The key identifier to the node that the user
 * wants to delete.
 */
void RBapp::processDelete(string& key)
{
  string data;
  cin.ignore();
  getline(cin,data);
  myRBT.rbDelete(key, data);
}