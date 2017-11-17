/**
 * @file minpriority.cpp Functions of class MinPriorityQ. 
 *
 * @brief
 *          Implementation of class member functions that
 *          belongs to the MinPriorityQ class. 
 *
 * @author Athit Vue
 * @date 12/5/2016
 */
#include "minpriority.h"

/* Constructor Nested Element Class */
MinPriorityQ::Element::Element()
{
  id = " ";
  key = 200;
}

/* Constructor for MinPriorityQ */
MinPriorityQ::MinPriorityQ(int size)
{
  heap_size = 0; // Initiate heap_size to zero. 
  minHeap = new Element[size+1];
}

/***************************
*--Public Functions Below--*
***************************/

/**
 * MinPriorityQ::insert
 *
 * Insert a string identifer with key. If the key is 0, 
 * then it is our source. Increase the heap size by 1 
 * and call decreaseKey to update the weight of the 
 * vertex. Call buildMinHeap. Else, if it is not our
 * source vertex, then it is a descendent of our source.
 * Increase heap size by 1 and set its key to infinity (200).
 * Call decreaseKey to insure min key is first to be extracted
 * from MinPriorityQ. 
 * 
 * @param id The key identifyer string.
 * @param key The priority number of the key. 
 */
void MinPriorityQ::insert(string id, int key)
{
  if(key == 0)
  {
    heap_size++;
    decreaseKey(id, key);
  }
  else
  {
    heap_size++;
    minHeap[heap_size].key = 200;   
    decreaseKey(id, key);
  }
  buildMinHeap();
}

/** 
 * MinPriorityQ::decreaseKey
 * 
 * Make sure the new key associated with the identifyer
 * string is less than the current key. If the newKey is greater
 * than the key in the MinPriorityQ, then swap the newKey
 * with the smaller key. Make the smaller key the parent in 
 * the minHeap. 
 *
 * @param id The key identifier of the element in minHeap.
 * @param newKey The new key. 
 */
void MinPriorityQ::decreaseKey(string id, int newKey)
{
  int i = heap_size;
  Element temp; // Instintiate an Object of Element class.
  
  minHeap[i].key = newKey;
  minHeap[i].id = id;
  
  /* While loop to check all the parent nodes in the minHeap
   * to make sure that they are truely less than its children.
   */
  while(i > 1 && minHeap[parent(i)].key > minHeap[i].key)
  {
    std::swap (minHeap[i], minHeap[parent(i)]);
    i = parent(i);
  }
}

/**
 * MinPriorityQ::extractMin
 *
 * Extract the element with the lowest key.
 * If heap size is < 1, then return "none". 
 * 
 * @return min.id Return the identifier id of the minimum Element.
 */
string MinPriorityQ::extractMin()
{
  if(heap_size < 1)
  {
    return "empty";
  }
  Element min = minHeap[1]; // Root of minHeap has smallest key.
  minHeap[1] = minHeap[heap_size];
  heap_size--;
  minHeapify(1);
  
  return min.id;
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
  for(int i = 1; i <= heap_size; i++)
  {
    if(minHeap[i].id == id)
    {
      return true;
    }
  }
  return false;
}

/**
 * MinPriorityQ::updateWeight
 * 
 * This function is needed to update the weight of
 * the key identifier string id.
 *
 * @param id The string identifier id.
 * @param key The priority key of the minHeap.
 */
void MinPriorityQ::updateWeight(string id, int key)
{
  for(int i = 1; i <= heap_size; i++)
  {
    if(minHeap[i].id == id)
    {
      minHeap[i].key = key;
    }
  }
  buildMinHeap();
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
  for(int i = ((heap_size) / 2); i >= 1; i--)
  {
    minHeapify(i); // Check the parent of the tree and subtrees.
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
  int L = left(i);
  int R = right(i);

  if(L <= heap_size && minHeap[L].key < minHeap[i].key)
  {
    smallest = L;
  }
  else
  {  
    smallest = i;
  }
  
  if(R <= heap_size && minHeap[R].key < minHeap[smallest].key)
  {  
    smallest = R;
  }
  
  if(smallest != i)
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
  return (i / 2);
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

