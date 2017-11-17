/**
 * @file rbtree.cpp Contains the functions of the red-black
 *                           tree class.
 *
 * @brief
 *            Implements the functions of the red-black tree.
 *
 * @author Athit Vue
 * @date 04/16/2016
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "rbtree.h"

using namespace std;

using std::cout;
using std::setw;
using std::endl;

/**
 * RBTree constructor.
 */
RBTree::RBTree()
{
  nil = new Node();
  root = nil;
}

/**
 * RBTree destructor.
 */
RBTree::~RBTree()
{
  //Delete the tree.
  while (root != nil)
  {
    rbDelete(root);
  }
  delete nil;
}

/*++++++++++++++++++++++++++
---Class Node Member Functions Below---
++++++++++++++++++++++++++*/

/**
 * Node class constructor
 */
RBTree::Node::Node()
{
  //Setting everything to NULL and default color to Black.
  parent = NULL;
  left = NULL;
  right = NULL;
  color = 'B';
}

/**
 * Destructor for Node class
 */
RBTree::Node::~Node()
{
 //Delete the key and value!
  delete key;
  delete value;
}

/**
 * RBTree::Node::Node
 *
 * This is an overloaded constructor for Node. It sets
 * the inserted key to member variable key and nil to 
 * the parent of the inserted Node and nil to the children
 * of the inserted Node. The new inserted Node is always 
 * red.
 * @param insertedKey    The key identifier that was inserted.
 * @param insertedValue The inserted value that belongs to 
 *                                        the key identifier.
 * @param node                Pointer variable to Node nil.
 */
RBTree::Node::Node(const string& k, const string& v, Node *node) 
{
  key = new string(k);
  value = new string(v);
  left = node;
  right = node;
  color = 'R';
  parent = node;
}

/*+++++++++++++++++++++++++++
---RBTree Class Member Functions Below---
+++++++++++++++++++++++++++*/

/**
 * RBTree::rbInsert
 *
 * This function inserts the key and data into a new 
 * Node. After that it inserts the key and data into the 
 * tree. It calls the overloaded private mutator 
 * rbInsert.
 *
 * @param key     The key identifyer of the Node.
 * @param value  The value that belongs to the key.
 */
void RBTree::rbInsert(const string& key, const string& value)
{
  rbInsert(new Node(key, value, nil)); 
}

/**
 * RBTree::rbDelete
 * 
 * This public member function utilizes the private accessor
 * function rbTreeSearch to find the node that the user wants
 * to delete and deletes it. 
 *
 * @param key    The key that identifies the Node.
 * @param value The value that belongs to the key.
 */
void RBTree::rbDelete(const string& key, const string& value)
{
  Node* temp = nil;
  //Search through the tree for a match, store it in temp.
  temp = rbTreeSearch (root, key);
  
  if (temp == nil)
  {
    return; //If temp is nil then tree is empty; return.
  }
  else 
  {
    //if value == value from node, then delete.
    if (*(temp->value) == value)
    {
      Node* node_found = temp;
      rbDelete (node_found);
      rbDelete (key, value);
      return;
    }
    //Using successor and predecessor functions to look for 
    //additional matches.
    Node* delete_successor;
    Node* current_temp_sNode = temp;
    delete_successor = rbTreeSuccessor (current_temp_sNode);
    //Check to see if successor matches node we want to delete.
    while (delete_successor != nil && 
      *(delete_successor->key) == key)
    {
      //If successor node's value == want to delete node's, then 
      //delete.
      if (*(delete_successor->value) == value)
      {
        rbDelete (delete_successor);
        rbDelete (key, value);
        delete_successor = nil; //Make the deleted successor a nil.
      }
      //Else if successor key == want to delete node's, but not 
      //successor's value, then look for the successor of current
      //successor's value to see if it matches what we want to 
      //delete.
      else
      {
        current_temp_sNode = delete_successor;
        delete_successor = rbTreeSuccessor (current_temp_sNode);
      }
    }
    //Now, let's make sure we check the predecessor as well.
    Node* delete_predecessor;
    Node* current_temp_pNode = temp;
    delete_predecessor = rbTreePredecessor (current_temp_pNode);
    while (delete_predecessor != nil && 
      *(delete_predecessor->key) == key)
    {
      if (*(delete_predecessor->value) == value)
      {
        rbDelete (delete_predecessor);
        rbDelete (key, value);
        delete_predecessor = nil;
      }
      else
      {
        current_temp_pNode = delete_predecessor;
        delete_predecessor = rbTreePredecessor (current_temp_pNode);
      }
    }
  }
}

/**
 * RBTree::rbFind
 *
 * This vector typed function is used to find nodes that have 
 * the same keys. It is used for the purpose of searching and 
 * deleting. 
 *
 * @param key The key identifier to a node.
 * @return value_vector Return the node from the values
 *                                       vector that had the same values.
 */
vector<const string*> RBTree::rbFind(const string& key)
{
  vector<const string*> value_vector;
  //Temp is a temp node for current node we are working on.
  Node *temp = nil;
  //Begin search from root
  temp = rbTreeSearch(root, key);
  if ((temp != nil) && *(temp->key) == key) 
  {
    //If key is found push from back to vector.
    value_vector.push_back(temp->value);
    //Need to find duplicates. 
    Node* successor_node;
    Node* find_sNode = temp;
    successor_node = rbTreeSuccessor(find_sNode);
    //If duplicate is found, push it in the back of vector and 
    //search for more by finding the newly founds successor.
    //Keep looking until we hit a nil.
    while (successor_node != nil && 
      *(successor_node->key) == key) 
    {
      value_vector.push_back (successor_node->value);
      find_sNode = successor_node;
      successor_node = rbTreeSuccessor(find_sNode);
    }
    //Now we need to look for predecessor node as well.
    //Same as above, keep looking for duplicates til nil.
    Node* predecessor_node;
    Node* find_pNode = temp;
    predecessor_node = rbTreePredecessor(find_pNode);
    while (predecessor_node != nil && 
      *(predecessor_node->key) == key) 
    {
      value_vector.push_back(predecessor_node->value);
      find_pNode = predecessor_node;
      predecessor_node = rbTreePredecessor(find_pNode);
    }
  }
  return value_vector;
}
  
/**
 * RBTree::rbPrintTree
 * 
 * This function calls the private accessor 
 * reverseInOrderPrint to print the tree sideways with 
 * the root in the most far-left side.
 */
void RBTree::rbPrintTree()
{
  reverseInOrderPrint(root, 0);
}

/*++++++++++++++++++++
---Private Accessors Are Below---
++++++++++++++++++++*/

/**
 * RBTree::Node* RBTree::rbTreeMinimum
 * 
 * This is a private accessor function to find a tree's minimum.
 * 
 * @param x The node in which we are concern with; the 
 *                  starting node to find the tree minimum. 
 * @return x The tree's minimum node which we want. 
 */
RBTree::Node* RBTree::rbTreeMinimum(Node* x)
{
  while (x->left != nil) //Go left until we find a nil.
  {
    x = x->left; //Set x to equal the Node right before we hit a nil.
  }
  return x;
}

/**
 * RBTree::Node* RBTree::rbTreeMaximum
 * 
 * This is a private accessor function to find a tree's maximum.
 * 
 * @param x The node in which we are concern with; the 
 *                  starting node to find the tree maximum. 
 * @return x The tree's maximum node which we want. 
 */
RBTree::Node* RBTree::rbTreeMaximum(Node* x)
{
  while (x->right != nil) //Go right until we find a nil.
  {
    x = x->right; //Set x to the node right before we hit nil.
  }
  return x;
}

/**
 * RBTree::Node* RBTree::rbTreeSuccessor
 *
 * This is a private accessor function to find the successor
 * of a tree.
 * 
 * @param x The node in which we are concerned with.
 * @return r  rbTreeMinimum(x->right) The successor of the
 *                   Node in which we are concerned with if x->right
 *                    != nil.
 * @return y  The successor.
 */
RBTree::Node* RBTree::rbTreeSuccessor(Node* x)
{
  if (x->right != nil)
  {
    return rbTreeMinimum(x->right);
  }
  Node* y = x->parent;
  while (y != nil &&  x == y->right)
  {
    x = y;
    x = y->parent;
  }
  return y;
}

/**
 * RBTree::Node* RBTree::rbTreePredecessor
 *
 * This is a private accessor function to find the 
 * predecessor of a tree.
 * 
 * @param x The node in which we are concerned with.
 * @return r  TreeMinimum(x->left) The predecessor of the
 *                   Node in which we are concerned with if 
 *                    x->left != nil.
 * @return y  The predecessor.
 */
RBTree::Node* RBTree::rbTreePredecessor(Node* x)
{
  if (x->left != nil)
  {
    return rbTreeMaximum(x->left);
  }
  Node* y = x->parent;
  while (y != nil &&  x == y->left)
  {
    x = y;
    x = y->parent;
  }
  return y;
}

/**
 * RBTree::Node* RBTree::rbTreeSearch
 *
 * This is a private accessor function search the tree to 
 * find the Node that matches the one we want to look for.
 * 
 * @param  x A pointer variable to the Node that we are 
 *                   currently looking at.
 * @param k The key identifier that we are searching for. 
 * @return x  The node that matches the key identifier or 
 *                   node that we are looking for. 
 * @return rbTreeSearch(x->left, k) Recursively call the 
 *                function until we find the node that we are 
 *                looking for on the left, if our key is less than
 *                the Node that we are currently looking at.
 * @return rbTreeSearch(x->right, k) Recursively call the 
 *                function until we find the node that we are 
 *                looking for on the right path of the tree, if our
 *                key is greater than the Node that we are 
 *                currently looking at. 
 */
RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& k)
{
  if ((x == nil) || (k == *(x->key))) 
  {
    return x;
  }
  if (k < *(x->key)) 
  {
    return rbTreeSearch(x->left, k);
  } 
  else 
  {
    return rbTreeSearch(x->right, k);
  }
}

/**
 * RBTree::reverserInOrderPrint
 *
 * This function is a private accessor function that walks
 * the tree from root and prints it in reverse order.
 *
 * @param x        The parent Node.
 * @param depth The depth of the tree. 
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/*++++++++++++++++++++
---Private Mutators Are Below---
++++++++++++++++++++*/

/**
 * RBTree::leftRotate
 *
 * This private mutator function rotates the current 
 * Node that we are currently looking at to the left.
 *
 * @param x The Node we are currently looking at.
 */
void RBTree::leftRotate(Node* x)
{
  Node* y = x->right;
  x->right = y->left;
  if (y->left != nil)
  {
    y->left->parent = x;
  }
  
  y->parent = x->parent;
  
  if (x->parent == nil)
  {
    root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

/**
 * RBTree::rightRotate
 *
 * This private mutator function rotates the current 
 * Node that we are currently looking at to the right.
 *
 * @param x The Node we are currently looking at.
 */
void RBTree::rightRotate(Node* x)
{
  Node* y = x->left; 
  x->left = y->right; 
  if (y->right != nil)
  {
    y->right->parent = x;
  }
  y->parent = x->parent; 
  if (x->parent == nil) 
  {
    root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else                         
  {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

/**
 * RBTree::rbInsertFixup
 *
 * This private mutator function fixes up the inserted nodes
 * to meet the properties of a red-black binary search tree.
 * 
 * @param z The Node that was inserted onto the tree.
 */
void RBTree::rbInsertFixup(Node* z)
{
  Node* y;
  while (z->parent->color == 'R')
  {
    if (z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right;
      if (y->color == 'R')
      {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->right)
        { 
          z = z->parent;
          leftRotate(z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(z->parent->parent);
      }
    }
    else
    {
      y = z->parent->parent->left;
      if (y->color == 'R')
      {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->left)
        {
          z = z->parent;
          rightRotate(z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(z->parent->parent);
      }
    }
  }
  root->color = 'B';
}
/**
 * RBTree::rbDeleteFixup
 *
 * This is a private mutator function that fixes up the 
 * tree after a deletion to make sure it meets the 
 * properties of a red-black binary search tree. 
 *
 * @param x The node to be deleted.
 */
void RBTree::rbDeleteFixup(Node* x)
{
  Node *w;
  while (x != root && x->color == 'B') 
  {
    if (x == x->parent->left) 
    {
      w = x->parent->right;
      if (w->color == 'R') 
      {
        w->color = 'B';
        x->parent->color = 'R';
        leftRotate (x->parent);
        w = x->parent->right;
      }
      if (w->left->color == 'B' && w->right->color == 'B') 
      {
        w->color = 'R';
        x = x->parent;
      } 
      else 
      {
        if (w->right->color == 'B') 
        {
          w->left->color = 'B';
          w->color = 'R';
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        leftRotate(x->parent);
        x = root;
      }
    } 
    else 
    {
      w = x->parent->left;
      if (w->color == 'R') 
      {
        w->color = 'B';
        x->parent->color = 'R';
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == 'B' && w->left->color == 'B') 
      {
        w->color = 'R';
        x = x->parent;
      }
      else 
      {
        if (w->left->color == 'B') 
        {
          w->right->color = 'B';
          w->color = 'R';
          leftRotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = 'B';
}

/**
 * RBTree::rbTransplant
 *
 * This private mutator function transplants two nodes. 
 * 
 * @param u The node removed from the tree or moved within
 *                  the tree.
 * @param v The node that moves into u's original position. 
 */
void RBTree::rbTransplant(Node* u, Node* v)
{
  if (u->parent == nil)
  {
    root = v;
  }
  else if ( u ==u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

/*++++++++++++++++++++++++++++++++++++
---Private Mutators Overloaded From Public Interface Below---
++++++++++++++++++++++++++++++++++++*/

/**
 * RBTree::rbInsert
 *
 * This is a overloaded private mutator for the insert function.
 * This function inserts the inserted key and value onto the tree. 
 * It then calls the private mutator function rbInsertFixup to 
 * fix the tree so that the properties for a red-black binary
 * search tree remains true. 
 *
 * @param z The node in which needs to be inserted onto the 
 *                  red-black tree.
 */
void RBTree::rbInsert(Node* z)
{
  Node* y = nil;
  Node* x = root;
  while (x != nil)
  {
    y = x;
    if (*z->key < *x->key)
    {
      x=x->left;
    }
    else
    {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == nil)
  {
    root = z;
  }
  else if (*z->key < *y->key) 
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
  
  z->left = nil;
  z->right = nil;
  z->color = 'R';
  rbInsertFixup(z);
}
/**
 * RBTree::rbDelete
 *
 * This is an overloaded private mutator function that does
 * the actual deletion of the node needed to be deleted.
 * It also calls private accessors and other private mutator
 * functions to keep the properties of a red-black binary
 * search tree true.
 * 
 * @param z The node being deleted.
 */
void RBTree::rbDelete(Node* z)
{
  Node* y = z;
  Node* x;
  //Must remember y's color or else seg fault d^_^b.
  char yColor = y->color;
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
    //Use predecessor instead of successor.
    y = rbTreeMaximum(z->left);
    //Must make sure we set y's color or else
    //seg fault d^_^b.
    yColor = y->color;
    x = y->left;
    if (y->parent == z)
    {
      x->parent = y;
    }
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
  {
    rbDeleteFixup(x);
  }
  delete z;
}