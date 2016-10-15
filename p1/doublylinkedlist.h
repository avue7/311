/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Athit Vue
 * @date 1/1/16; modified: 2/01/2016
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

#include <assert.h>
#include <iostream> //delete me
using namespace std;
template <class T>
class DoublyLinkedList 
{
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();
        void append(T* data);
        bool empty() const { return (head == nullptr); }
        T* remove();
        T* first();
        T* next();

    private:
        class Node 
        {
            public:
                Node();
                Node(T* data);
                Node* next;
                Node* prev;
                T* data;
        };
        Node* head;
        Node* tail;
        Node* current;
};

/**
 * @brief   Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node(T* data) 
{
    next = nullptr;
    prev = nullptr;
    this->data = data;
}
/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

/**
 * @brief   DoublyLinkedList destructor.
 */
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    Node* ptr = head;
    while (ptr != nullptr)
    {
        Node* dest_remove;
        dest_remove = ptr;
        ptr = ptr->next;
        delete dest_remove;
    }
    tail = nullptr;
}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data)
{
    if (empty())
    {
        current = tail;
        head = tail = new Node(data);
    }
    else
    {
        current = tail;
        tail->next = new Node(data);
        tail = tail->next;
    }
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first()
{
    if (empty())
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        return nullptr;
    }
    else
    {
        current = head;
        return head->data;
    }
}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next()
{
    if(empty())
    {
        tail = nullptr;
        head = nullptr;
        current = nullptr;
        return nullptr;
    }
    else
    {
        current = current->next;
        return current->data;
    }
}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove()
{
    if(empty())
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        return nullptr;
    }
    if(current == head)
    {
        if(head == nullptr)
        {
            return nullptr;
        }
        else if(head->next == nullptr)
        {
            Node* del_head = head;
            head = tail = nullptr;
            current = nullptr;
            delete del_head;
            return nullptr;
        }
        else
        {
            Node* m_head = head;
            head = head->next;
            delete m_head;
            head->prev = nullptr;
            current = head;
            m_head = nullptr;
            return current->data;
        }
    }   
    else if(current == tail)
    {
        if(tail == nullptr)
        {
            head = nullptr;
            current = nullptr;
            return nullptr;
        }
        else if (tail->prev == nullptr)
        {
            Node* tail_ptr = tail;
            head = tail = nullptr;
            current = nullptr;
            delete tail_ptr;
            return nullptr;
        }
        else
        {
            Node* tail_temp = tail;
            tail = tail->prev;
            current = nullptr;
            delete tail_temp;
            tail_temp = nullptr;
            tail->next = nullptr;
            return nullptr;
        }
    }
    else
    {
        Node* new_current = current;
        new_current = current->prev->next; 
        new_current->next = current->next;
        delete current;
        current = new_current->next;
        current->next = current->next;
        current->prev = current->prev;
        return current->data;
    }
}


#endif // CSCI_311_DOUBLYLINKEDLIST_H
