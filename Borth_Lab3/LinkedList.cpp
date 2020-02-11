/* -----------------------------------------------------------------------------
 *
 * File Name:  LinkedList.cpp
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 1 - Implementation of Singly Linked List
 * Description:  LinkedList methods are defined.
 * Date: 2/2/20
 *
 ---------------------------------------------------------------------------- */

//#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
	m_length = 0;
	m_front = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& original)
{
	operator=(original);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
	m_front = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& original)
{
	int index = 1;

	while (index < original.getLength() + 1)
	{
		insert(index, original.getEntry(index));
	}
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
	if(m_length == 0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

template <typename T>
int LinkedList<T>::getLength() const
{
	return(m_length);
}

template <typename T>
void LinkedList<T>::insert(int position, T entry)
{
	if (position == 1)
	{
		Node<T>* temp = m_front;
		m_front = new Node<T>(entry);
		m_front->setNext(temp);
		m_length++;
	}
	else if (position == m_length + 1)
	{
		int index = 1;
		Node<T>* m_back = m_front;
		Node<T>* m_order = m_front;
		Node<T>* temp = nullptr;

		while (index < position)
		{
			m_back = m_back->getNext();
			if (index + 1 != position)
			{
				m_order = m_back;
			}
			index++;
		}

		m_back = new Node<T>(entry);
		m_back->setNext(temp);
		m_order->setNext(m_back);
		m_length++;
	}
	else if ((position > 1) && (position < m_length + 1))
	{
		int index = 1;
		Node<T>* m_back = m_front;
		Node<T>* m_order = m_front;
		Node<T>* temp = nullptr;

		while (index < position)
		{
			m_back = m_back->getNext();
			if (index + 1 != position)
			{
				m_order = m_back;
			}
			index++;
		}

		temp = m_back;
		m_back = new Node<T>(entry);
		m_back->setNext(temp);
		m_order->setNext(m_back);
		m_length++;
	}
	else
	{
		throw(runtime_error("ERROR! Invalid position.\n"));
	}
}

template <typename T>
void LinkedList<T>::remove(int position)
{
	if (!isEmpty())
	{
		if (position == 1)
		{

			Node<T>* m_back = m_front;
			Node<T>* temp = m_front;
			m_back = m_back->getNext();
			temp->~Node<T>();
			m_front = m_back;
			m_length--;

		}
		else if (position == m_length)
		{
			int index = 1;
			Node<T>* m_back = m_front;

			while (index < position)
			{
				m_back = m_back->getNext();
				index++;
			}

			m_back->~Node<T>();
			m_length--;
		}
		else if ((position > 1) && (position < m_length))
		{
			Node<T>* temp = m_front;
			Node<T>* m_previous = m_front;
			Node<T>* m_next = m_front;

			for (int i = 1; i <= position; i++)
			{
				m_next = m_next->getNext();

				if(i < position)
				{
					temp = temp->getNext();
				}

				if(i < position - 1)
				{
					m_previous = m_previous->getNext();
				}
			}

			m_previous->setNext(m_next);
			temp->setNext(nullptr);
			temp->~Node<T>();
			m_length--;
		}
		else
		{
			throw(runtime_error("ERROR! Invalid position.\n"));
		}
	}
}

template <typename T>
void LinkedList<T>::clear()
{
	while(!isEmpty())
	{
		Node<T>* m_back = m_front;
		Node<T>* temp = m_front;
		m_back = m_back->getNext();
		temp->~Node<T>();
		m_front = m_back;
		m_length--;
	}
}

template <typename T>
T LinkedList<T>::getEntry(int position) const
{
	Node<T>* temp = m_front;

	if ((position >= 1) && (position <= m_length))
	{
		for (int i = 1; i < position; i++)
		{
			temp = temp->getNext();
		}
		return(temp->getEntry());
	}
	else
	{
		throw(runtime_error("ERROR! Invalid position.\n"));
	}
}

template <typename T>
void LinkedList<T>::replace(int position, T newEntry)
{
	LinkedList::remove(position);
	insert(position, newEntry);
}
