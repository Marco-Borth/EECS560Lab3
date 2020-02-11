/* -----------------------------------------------------------------------------
*
* File Name:  Node.h
* Author: Marco Borth
* Assignment:   EECS-560 Lab 1 - Implementation of Singly Linked List
* Description:  Node Template Class is constructed;
* Date: 2/2/20
*
---------------------------------------------------------------------------- */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Node
{
private:
  T m_entry;
  Node<T>* m_next;

public:
/*
* @pre none.
* @param entry must be a int value.
* @post m_entry is set to entry.
*/
  void setEntry(T entry);

/*
* @pre none.
* @post return m_entry value.
*/
  T getEntry() const;

/*
* @pre none.
* @param next must be a Node or Node pointer.
* @post m_next is set to next.
*/
  void setNext(Node* next);

/*
* @pre none.
* @post return m_next.
*/
  Node<T>* getNext() const;

/*
* @pre none.
* @param entry must be a valid int entry
* @post creates node with givin int entry.
*/
  Node(T entry);

/*
* @pre Node object must be constructed.
* @post deletes Node, m_entry, and m_next = nullptr.
*/
  ~Node<T>();
};

#include "Node.cpp"

#endif
