#include <iostream>
#include <string>
#include "DoublyLinkedList.h"

using namespace std;

/**
 * Returns true if the list is empty, false if it had nodes.
 */
bool DoublyLinkedList::empty()
{
  if(m_head == NULL) //&& m_tail == NULL)
    return true;
  else
    return false;
      
}

/**
 * Appends songs to the end of list.
 *
 * Checks to see if list is empty or has nodes, appends new node accordingly.
 */
void DoublyLinkedList::append(string& s)
{
  if(m_head == NULL) //check to see if list is empty
  {
    m_head = new Node(s, NULL, NULL);
    m_tail = m_head;
    m_current = m_head;    
  }
  else
  {
    /* Node *ptr = m_tail;
    m_tail = new Node(s, NULL, ptr); //node(song, next, previous)
    ptr->m_next = m_tail; */
        
    //create new node, tell last node that new node is after, point tail at new node
    Node *ptr = new Node(s, m_current->m_next, m_current); //node(song, next, previous)
    if(m_current->m_next != NULL)
      m_current->m_next->m_prev = ptr;
    else
      m_tail = ptr;
      
    m_current->m_next = ptr;
    m_current = ptr;
  }
      
}


/**
 * Insert before song.
 *
 * checks for empty list, inserts song before current.
 */
void DoublyLinkedList::insertBefore(string& s)
{
  
  if(m_head == NULL)
  {
    m_head = new Node(s, NULL, NULL);
    m_tail = m_head;
    m_current = m_head;
    
  }
  else if(m_current->m_prev == NULL)
  {
    Node *ptr = new Node(s, m_head, NULL);
    m_head->m_prev = ptr;
    m_head = ptr;
    m_current = m_head;  
  }
  else
  {
    Node *ptr = new Node(s, m_current, m_current->m_prev);
    ptr->m_prev->m_next = ptr;
    m_current->m_prev = ptr;
    m_current = ptr;
  }
}
    

/**
 * insert after command.
 *
 * checks for an empty list, inserts song after current.
 */    
void DoublyLinkedList::insertAfter(string& s)
{
  if(m_head == NULL)
  {
    m_head = new Node(s, NULL, NULL);
    m_tail = m_head;
    m_current = m_head;
                        
  }
  else if(m_current->m_next == NULL)
  {
    Node *ptr = new Node(s, NULL, m_current);
    m_current->m_next = ptr;
    m_tail = ptr;
    m_current = ptr;  
  }
  else
  {
    Node *ptr = new Node(s, m_current->m_next, m_current);
    ptr->m_next->m_prev = ptr;
    m_current->m_next = ptr;
    m_current = ptr;
  }
}
    

/**
 * Remove song command.
 *
 * calls find function, if find returns true, checks if only node,
 * if last node, first node, or in-between and deletes accordingly
 */    
void DoublyLinkedList::remove(string& s)
{
  if(find(s))
  {
    Node *temp = m_current;
    
    if(temp->m_next == NULL && temp->m_prev == NULL)
    {
      m_current = NULL;
      m_head = NULL;
      m_tail = NULL;
      delete temp;
    }

    else if(temp->m_next == NULL)  //is last node
    {
      temp->m_prev->m_next = NULL;
      m_tail = temp->m_prev;
      m_current = m_tail;
      delete temp;
    }
    
    else if(temp->m_prev == NULL)  //is first node
    {
      temp->m_next->m_prev = NULL;
      m_head = temp->m_next;
      m_current = m_head;
      delete temp;
    
    }
    
    else if(temp->m_prev != NULL && temp->m_next != NULL) //nodes on both sides
    {
      temp->m_prev->m_next = temp->m_next;
      m_current = temp->m_next;
      m_current->m_prev = temp->m_prev;
    
      delete temp;
    }
  }
}


/**
 * moves current to top of list.
 */    
void DoublyLinkedList::begin()
{
  m_current = m_head;
  
}    


/**
 * moves current to last song in list.
 *
 *
 */    
void DoublyLinkedList::end()
{
  m_current = m_tail;
  
}    


/**
 * moves current to next song.
 *
 */    
bool DoublyLinkedList::next()
{
  if(m_current->m_next != NULL)
  {
    m_current = m_current->m_next;
    return true;
  }
  else
    return false;
}    

/**
 * moves current to previous song.
 *
 */        
bool DoublyLinkedList::prev()
{
  if(m_current->m_prev != NULL)
  {
    m_current = m_current->m_prev;
    return true;
  }
  else
    return false;
}    

/**
 * Finds if song is in list, returns true or false.
 *
 */    
bool DoublyLinkedList::find(string& s)
{
  Node *temp = m_head;
  while(temp)
  {
    if(temp->m_song == s) //song found
    {
      m_current = temp;
      return true;
    }
    else 
      temp = temp->m_next;
  }
  return false;
}    

/**
 * returns song title.
 *
 */    
    
const string& DoublyLinkedList::getData()
{
  
  return m_current->m_song;
} 