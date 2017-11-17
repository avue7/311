#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "rbtree.h"

using namespace std;

//*************************
//*RBTree public functions*
//*************************

//RBTree constructor
RBTree::RBTree()
{
  nil = new Node();
  root = nil;
}

//RBTree destructor
RBTree::~RBTree()
{
  delete root;
  delete nil;
}

//inserts key and data into new node then inserts into tree
void RBTree::rbInsert(const string& key, const string& data)
{
  rbInsert(new Node(key, data, nil));  //calls overloaded insert
}

//finds nodes that match and deletes them
void RBTree::rbDelete(const string& key, const string& data)
{
  Node* x = rbTreeSearch(root, key);
  vector<Node*> deleteVector;
  bool found = false;
  
  if(x!= nil && *x->value == data)
  {
    Node *successor = rbTreeSuccessor(x);
    Node *predecessor =  rbTreePredecessor(x);
    deleteVector.push_back(x);
    while(successor != nil)
    {
      if (successor != x && *successor->key == key && *successor->value == data)
      {
        for(unsigned int i = 0; i < deleteVector.size(); i++)
        {
          if (deleteVector[i] == successor)
            found = true;
        }
        if(!found)
          deleteVector.push_back(successor);
      }
      successor = rbTreeSuccessor(successor);
    }
    
    while(predecessor != nil)
    {
      if (predecessor != x && *predecessor->key == key && *predecessor->value == data)
      {
        for(unsigned int i = 0; i < deleteVector.size(); i++)
        {
          if (deleteVector[i] == predecessor)
            found = true;
        }
        if(!found)
          deleteVector.push_back(predecessor);
      }
      predecessor = rbTreeSuccessor(predecessor);

    }
    
    for(unsigned int i = 0; i < deleteVector.size(); i++)
    {
      if(*deleteVector[i]->value == data)
        rbDelete(deleteVector[i]);
    }
  }
}

//finds nodes with same keys
vector<const string*> RBTree::rbFind(const string& key)
{
  vector<Node*> nodeVector;
  vector<const string*> valuesVector;
  Node *x = rbTreeSearch(root, key);

  if(x != nil)  //make sure there is a match
  {
    Node *successor = rbTreeSuccessor(x);
    Node *predecessor =  rbTreePredecessor(x);
    nodeVector.push_back(x);
    while(successor != nil)
    {
      if (successor != x && *successor->key == *x->key)
        nodeVector.push_back(successor);
      
      successor = rbTreeSuccessor(successor);
    }
    
    while(predecessor != nil)
    {
      if (predecessor != x && *predecessor->key == *x->key)
        nodeVector.push_back(predecessor);
      
      predecessor = rbTreeSuccessor(predecessor);
    }

    for(unsigned int i = 0; i < nodeVector.size(); i++)
    {
      valuesVector.push_back(nodeVector[i]->value);
    }
  }
  return valuesVector;
}

//
void RBTree::rbPrintTree()
{
  reverseInOrderPrint(root, 0);
}

//**************************
//*RBTree Private functions*
//**************************

//*******************
//*RBTree Node Class*
//*******************

//Node constructor
RBTree::Node::Node()
{
  parent = NULL;
  left = NULL;
  right = NULL;
  key = NULL;
  value = NULL;
  color = 'B';
}

//Node destructor
RBTree::Node::~Node()
{
  if(left == NULL)
    delete left;
  else if(left->key != NULL)
    delete left;
  
  if(right == NULL)
    delete right;
  else if(right->key != NULL)
    delete right;
    
  delete key;
  delete value;

}

//Node overloaded constructor
RBTree::Node::Node(const string& inputKey, const string& inputData, Node *nodeNil)
{
  key = new string(inputKey);
  value = new string(inputData);
  left = nodeNil;
  right = nodeNil;
  color = 'R';
  parent = nodeNil;
}

//**************************
//*RBTree Private Accessors*
//**************************

//Finds a tree's minimum
RBTree::Node* RBTree::rbTreeMinimum(Node* x)
{
  while (x->left != nil)
    x = x->left;
  return x;
}

//finds a tree's maximum
RBTree::Node* RBTree::rbTreeMaximum(Node* x)
{
  while (x->right != nil) 
    x = x->right;
  return x;
}

//finds a node's Successor
RBTree::Node* RBTree::rbTreeSuccessor(Node* x)
{
  if (x->right != nil)
    return rbTreeMinimum(x->right);
  Node* y = x->parent;
  while (y != nil && x == y->right)
  {
    x = y;
    y = y->parent;
  }
    return y;
}

//finds a node's predecessor
RBTree::Node* RBTree::rbTreePredecessor(Node* x)
{
  if (x->left != nil)
    return rbTreeMaximum(x->left);
  Node* y = x->parent;
  while (y != nil && x == y->left)
  {
    x = y;
    y = y->parent;
  }
  return y;
}

//searches the tree for nodes that match
RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& k)
{
  if (x == nil)
    return x;
  else if (k == *x->key) 
    return x; 
  if (k < *x->key)
    return rbTreeSearch(x->left, k);
  else return rbTreeSearch(x->right, k);
}

//prints tree in reverse in order
void RBTree::reverseInOrderPrint(Node *x, int depth)
{
  if (x != nil)
  {
    reverseInOrderPrint(x->right, depth+1);
    cout << setw(depth*4+4) << x->color << " ";
    cout << *(x->key) << *(x->value) << endl;
    reverseInOrderPrint(x->left, depth+1);
  }
}

//*************************
//*RBTree Private Mutators*
//*************************

//Take your partner and rotate to the left
void RBTree::leftRotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;             //turn y's left subree into x's right subtree
  if (y->left != nil)
    y->left->parent = x;
  y->parent = x->parent;          //x's parent is now y's
  if (x->parent == nil)           //if x was root, now y is root
    root = y;
  else if ( x == x->parent->left) //if x is it's parent's left
    x->parent->left = y;
  else                            //if x is it's parent's right
    x->parent->right = y;
  y->left = x;                    //x is now on y's left
  x->parent = y;                  //y is now x's parent
}

//Take your partner and rotate to the right
void RBTree::rightRotate(Node* x)
{
  Node* y = x->left;
  x->left = y->right;             //turn y's right subree into x's left subtree
  if (y->right != nil)
    y->right->parent = x;
  y->parent = x->parent;          //link x's parent to y
  if (x->parent == nil)           //if x was root, y now root
    root = y;
  else if (x == x->parent->right)//if x is it's parent's right
    x->parent->right = y;
  else                            //if x wasn't
    x->parent->left = y;
  y->right = x;                   //x is now on y's right
  x->parent = y;                  //y is now x's parent
}

//fixes the tree when a node gets inserted
void RBTree::rbInsertFixup(Node* z)
{
  while (z->parent->color == 'R')
  {
    if (z->parent == z->parent->parent->left)  //z's parent is its parent's left child
    {
      Node* y=z->parent->parent->right;
      if (y->color == 'R')//Case 1
      {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      }
      else if (z == z->parent->right)//Case2
      { 
        z = z->parent;
        leftRotate(z);
      }
      else//case3
      {
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(z->parent->parent);
      }
    }
    else  //z's parent is its parent's right child
    {
      Node* y=z->parent->parent->left;
      if (y->color == 'R')
      {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      }
      else if (z == z->parent->left)
      {
        z = z->parent;
        rightRotate(z);
      }
      else
      {
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(z->parent->parent);
      }
    }
  }
  root->color = 'B';  //gotta make sure the root is black!
}

//fixes the tree when a node is deleted
void RBTree::rbDeleteFixup(Node* x)
{
  while (x != root && x->color == 'B')
  {
    if (x == x->parent->left)  //If x is left child of its parent
    {
      Node* w = x->parent->right;
      if (w->color == 'R')  //Case 1 - x is red
      {
        w->color = 'B';
        x->parent->color = 'R';
        leftRotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == 'B' && w->right->color == 'B')//Case 2 - x is black, and both children are black
      {
        w->color = 'R';
        x = x->parent;
      }
      else if (w->right->color == 'B')  //Case 3 - x is black, x's left child is red and right is black
      {
        w->left->color = 'B';
        w->color = 'R';
        rightRotate(w);
        w = x->parent->right;
      }
      else  //Case 4 - x is black, and x's right child is red. 
      {
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        leftRotate(x->parent);
        x = root;
      }
    }
    else  //If x is the right child of its parent
    {   
      Node* w = x->parent->left;
      if (w->color == 'R')  //case1 - x is red
      {
        w->color = 'B';
        x->parent->color = 'R';
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == 'B' && w->left->color == 'B')//case2 - x is black, and both children are black
      {
        w->color = 'R';
        x = x->parent;
      }
      else if (w->left->color == 'B')//case3 - x is black, x's left child is red and right is black
      {
        w->right->color = 'B';
        w->color = 'R';
        leftRotate(w);
        w = x->parent->left;
      }
      else//case4 - x is black, and x's right child is red.
      {
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        rightRotate(x->parent);
        x = root;
      }
    } 
  }
  x->color = 'B';  //gotta make sure the root is black
}

//transplants two nodes
void RBTree::rbTransplant(Node* u, Node* v)
{
  if (u->parent == nil)
    root = v;
  else if ( u ==u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  
  v->parent = u->parent;
}


//************************************
//*RBTree Private Overloaded Mutators*
//************************************

//overloaded insert
void RBTree::rbInsert(Node* z)
{
  Node* y = nil;
  Node* x = root;
  while (x != nil)
  {
    y = x;
    if (*z->key < *x->key) 
      x=x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == nil)
    root = z;
  else if (*z->key < *y->key) 
    y->left = z;
  else
    y->right = z;
  
  z->left = nil;
  z->right = nil;
  z->color = 'R';
  
  rbInsertFixup(z);
}

//overloaded delete
void RBTree::rbDelete(Node* z)
{
  Node* y = z;
  Node* x;
  char yColor = y->color; //place holder for y's color
  if (z->left == nil)
  {
    x = z->right;
    rbTransplant(z, z->right);
  }
  else if (z->right == nil)
  {
    x = z->left;
    rbTransplant(z, z->left);
  }
  else
  {
    y = rbTreeMaximum(z->left); //Uses predecessor, same as RB tree visualization
    x = y->left;
    if (y->parent == z)
      x->parent = y;
    else
    {
      rbTransplant(y, y->left);
      y->left = z->left;
      y->left->parent = y;
    }
    rbTransplant(z, y);
    y->right = z->right;
    y->right->parent= y;
    y->color = z->color;
  }
  if (yColor == 'B')
    rbDeleteFixup(x);
    
  z->left = NULL;
  z->right = NULL;
  delete z;
}
