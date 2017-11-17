#ifndef _DOUBLYLINKEDLIST_H_
#define _DOUBLYLINKEDLIST_H_


#include <iostream>
#include <string>

using namespace std;

class DoublyLinkedList
{
  private:
    class Node
    {
      public:
        Node(string& song, Node *next, Node *prev)         //creates node object
        {m_song = song;m_next = next; m_prev = prev;}
        Node *m_next, *m_prev;                             //creates pointers to fill nodes
        string m_song;                                     //creates song name
        ~Node(){}                                          //node deconstructor
    };
  
  Node *m_head, *m_tail, *m_current;                       //pointers for current, head, and tail

  public:
    DoublyLinkedList(): m_head(NULL), m_tail(NULL), m_current(NULL){} //constructor for DLL
    bool empty();                                          //check if empty function
    void append(string& s);                                //append to end function
    void insertBefore(string& s);                          //insert before current function
    void insertAfter(string& s);                           //insert after current function
    void remove(string& s);                                //remove current node function
    void begin();                                          //goto beginning of list
    void end();                                            //goto end of list
    bool next();                                           //move current to next if possible
    bool prev();                                           //move current to previous if possible
    bool find(string& s);                                  //find song
    const string& getData();                               //get song title
    ~DoublyLinkedList()                                    //deconstructor for list
    {
      while(m_tail)
      {
         m_current = m_tail;
         m_tail = m_tail->m_prev;
         delete m_current;
      }
      
      
    } 
  
};
#endif