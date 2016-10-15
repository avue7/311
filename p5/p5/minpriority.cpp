/**
 * @file minpriority.cpp Functions of minpriority
 *
 * @brief
 *            Implements the class member functions of 
 *  of the MinPriority Class and nested Subclass 
 *  Element.
 *
 * @author Athit Vue
 * @date 5/02/2016
 */
#include "minpriority.h"
using std::cout;
using std::endl;


/*Constructor for MinPriorityQ*/
MinPriorityQ::MinPriorityQ(/*int size*/)
{
}
/*Destructor*/
MinPriorityQ::~MinPriorityQ()
{
}

bool MinPriorityQ::isEmpty()
{
  if(minHeap.size() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
    
/***************************
*--Public Functions Below--*
***************************/

/**
 * MinPriorityQ::insert
 *
 * Insert a string identifer with key into a temporary
 * Element class. Insert the temp Element in the 
 * back of the minHeap. If there is more than one 
 * element in the vector then call buildMinheap to 
 * build a minimum priority heap.
 * 
 * @param id The key identifyer string.
 * @param key The priority number of the key. 
 */
void MinPriorityQ::insert(string id, int key)
{
  Element temp(id, key);
  minHeap.push_back(temp);
  if(minHeap.size() >= 1)
  {
    buildMinHeap();
  }
}

/**
 * MinPriorityQ::decreaseKey
 *
 * Make sure that the new key asscociated with the 
 * identifier string is less than the current key; 
 * ensuring decrease only. Update the element's key
 * value to the new key. Then traverse the tree 
 * upward comparing element with string id to its 
 * parent and swapping keys if neccessary until the 
 * string id's key larger than it's parent's key. We 
 * want to ensure that the children node's parent is
 * smaller. 
 * 
 * @param id The key identifier to the element.
 * @param newKey The updated key used as a 
 *                            priority number. 
 */
void MinPriorityQ::decreaseKey(string id, int newKey)
{
  unsigned int i;
  for (i = 0; i < minHeap.size(); i++)
  {
    if (minHeap[i].id == id)
    {
      if (newKey > minHeap[i].key)
      {
        cout << 
        "new key is greater than current key!!!!" 
        << endl;
        break;
      }
      else
      {
        minHeap[i].key = newKey;
        while(i > 0 && minHeap[parent(i)].key > 
          minHeap[i].key)
        {
          std::swap (minHeap[i], minHeap[parent(i)]);
          i = parent(i);
        }
      }
    }
  }
}

/**
 * MinPriorityQ::extractMin
 *
 * First off, make sure that the heap is not empty. If
 * it is then return a string telling the user that it is
 * empty. Else, make a copy of the minimum element 
 * Use front() to get min. Make the last node of 
 * the tree the new root. Then erase the last node 
 * from the tree. Re-heapify the minheap passing 
 * arguments 0 (the index to root). Finally, 
 * return the minimum value as a string for output.
 *
 * @return min The minumum node of the tree.
 */
string MinPriorityQ::extractMin()
{
  string min;
  if (minHeap.size() <= 0)
  {
    return "empty";
  }
  else
  {
    min = minHeap.front().id;
    std::swap (minHeap.front(), minHeap.back());
    minHeap.pop_back();
    minHeapify(0);
    return min;
  }
}

/**
 * MinPriorityQ::isMember
 * 
 * Transverse through the heap and try to find the 
 * key identifier by its string id. If found then return
 * true. If the key identifier is not found, then return
 * false. 
 * 
 * @param id The key identifier of the element. 
 * @return bool If key is found return true. Else
 *                       return false;
 */
bool MinPriorityQ::isMember(string id)
{
  unsigned int i;
  for (i = 0; i < minHeap.size(); i++)
  {
    if (id == minHeap[i].id)
    {
      return true;
    }
  }
  return false;
}

/***************************
*--Private Functions Below--*
***************************/

/**
 * MinPriorityQ::buildMinHeap
 *
 * Build a min-heap from an unordered array. In this 
 * case, from an unordered vector. A min-heap is 
 * truely a min-heap if the parent of each tree is less 
 * then it's children, from the bottom 
 * all the way up to the root. So call minHeapify to 
 * check each of the parent of the trees to make sure 
 * that it is less than it's children up to the root. 
 */
void MinPriorityQ::buildMinHeap()
{
  //Int i is the parent of a min-heap tree.
  for (int i = ((minHeap.size() / 2) - 1); i >= 0; i--)
  {
    minHeapify(i); //Check the parent of the tree and 
                            //subtrees.
  }
}

/**
 * MinPriorityQ::minHeapify
 * 
 * This function is used to maintain the property of 
 * the min-heap. The parent at each tree must be 
 * less than it's children. That parent then must be 
 * also less then it's parent. Keep checking
 * to make sure this property exist all the way up to 
 * the root. Swap if neccessary. 
 *
 * @param i The root of the tree or subtrees. 
 */
void MinPriorityQ::minHeapify(int i)
{
  int smallest;
  unsigned int l = left(i); //Set parent i's left child.
  unsigned int r = right(i); //Set parent i's right child.
  //If parent i's left child's priority key is smaller 
  //then smallest equals left child.
  if (l < minHeap.size() && minHeap[l].key < 
    minHeap[i].key)
  {
    smallest = l;
  }
  else // Else parent's priority key IS the smallest.
  {
    smallest = i;
  }
  //If parent i's right child's priority key is smaller 
  //then smallest equals right child. 
  if (r < minHeap.size() && minHeap[r].key 
      < minHeap[smallest].key)
  {
    smallest = r;
  }
  //If the smallest was found and it wasn't the 
  //original parent i do a swap and do a recursively call.
  if (smallest != i)
  {
    std::swap(minHeap[i], minHeap[smallest]);
    minHeapify(smallest);
  }
}

/**
 * MinPriorityQ::parent
 *
 * Find the parent of the min-heap.
 * 
 * @param i The current element to find it's parent. 
 * @return int Must return the parent of element i. 
 */
int MinPriorityQ::parent(int i)
{
  return (i  / 2);
}

/**
 * MinPriorityQ::left
 * 
 * Find the left child of element i. 
 * 
 * @param i The index of the current element. 
 * @return int (2*i) is the element i's left child. 
 */
int MinPriorityQ::left(int i)
{
  return (2 * i);
}    

/**
 * MinPriorityQ::right
 * 
 * Find the right child of element i.
 * 
 * @param i The index of the element i.
 * @return int (2*i)+1 is the element i's right child. 
 */
int MinPriorityQ::right(int i)
{
  return (2 * i) + 1;
}
