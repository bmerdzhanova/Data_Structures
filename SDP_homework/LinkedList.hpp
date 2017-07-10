/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Betina Merdzhanova
* @idnumber 45151
* @task 4
* @compiler VC
*
*/
#ifndef LINKED_LIST_HEADER_INCLUDED
#define LINKED_LIST_HEADER_INCLUDED

#include "Iterator.hpp"

template <class T>
class LinkedList
{
private:
	struct linkedListNode
	{
		T data;
		linkedListNode* next;
		linkedListNode(T d, linkedListNode* n = nullptr)
		{
			data = d;
			next = n;
		}
	};
	linkedListNode* front;
	linkedListNode* back;
	int curSize;
public:
	LinkedList();
	LinkedList(const LinkedList<T>&);
	LinkedList& operator=(const LinkedList<T>&);
	~LinkedList();
	
	void pushBack(const T&);
	void pushFront(const T&);

	const T& getBack() const;
	const T& getFront() const;

	void popBack();
	void popFront();
	void pop(const T&);

	bool search(const T&) const;

	bool isEmpty() const;

	Iterator<T> beg() { return Iterator(front); }
	Iterator<T> end() { return Iterator(back->next); }
	void setSize(int);
	int getSize() const;
private:
	void copy(const LinkedList<T>&);
	void clean();

};

template <class T>
LinkedList<T>::LinkedList()
{
	front = nullptr;
	back = nullptr;
	curSize = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	copy(other);
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	clean();
}

template <class T>
void LinkedList<T>::copy(const LinkedList<T>& other)
{
	if (other.isEmpty())
		return;

	front = new linkedListNode(other.front->data);
	linkedListNode* toCopy = other.front;
	linkedListNode* copier = front;

	while (toCopy->next != nullptr)
	{
		toCopy = toCopy->next;
		copier->next = new linkedListNode(toCopy->data);
		copier = copier->next;
	}
	back = copier;
	curSize = other.curSize;
}

template <class T>
void LinkedList<T>::clean()
{
	linkedListNode* destr;
	while (front != nullptr)
	{
		destr = front;
		front = front->next;
		delete destr;
	}
	front = nullptr;
	back = nullptr;
	curSize = 0;
}

template <class T>
void LinkedList<T>::pushBack(const T& elem)
{
	if (isEmpty())
	{
		front = new linkedListNode(elem);
		back = front;
		curSize++;
		return;
	}

	back->next = new linkedListNode(elem);
	back = back->next;
	curSize++;
}


template <class T>
void LinkedList<T>::pushFront(const T& elem)
{
	if (isEmpty())
	{
		front = new linkedListNode(elem);
		back = front;
		curSize++;
		return;
	}

	linkedListNode* newEl = new linkedListNode(elem);
	newEl->next = front;
	front = newEl;
	curSize++;
}

template <class T>
const T& LinkedList<T>::getBack() const
{
	if (isEmpty())
		throw std::exception("The list is empty!");
	return back->data;
}

template <class T>
const T& LinkedList<T>::getFront() const
{
	if (isEmpty())
		throw std::exception("The list is empty!");
	return front->data;
}

template <class T>
void LinkedList<T>::popBack()
{
	if (isEmpty())
		throw std::exception("The list is empty!");

	if (curSize == 1)
	{
		delete front;
		front = nullptr;
		back = nullptr;
		curSize = 0;
	}

	linkedListNode* destr = front;

	while (destr->next != back)
	{
		destr = destr->next;
	}
	delete back;
	back = destr;
	back->next = nullptr;
	curSize--;
}

template <class T>
void LinkedList<T>::popFront()
{
	if (isEmpty())
		throw std::exception("The list is empty!");

	linkedListNode* destr = front;
	front = front->next;
	delete destr;
	curSize--;
}

template <class T>
bool LinkedList<T>::search(const T& el) const
{
	linkedListNode* cur = front;

	while (cur != nullptr)
	{
		if (cur->data == el)
			return true;
		cur = cur->next;
	}
	return false;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
	return curSize == 0;
}

template <class T>
void LinkedList<T>::setSize(int size)
{
	curSize = size;
}

template <class T>
int LinkedList<T>::getSize() const
{
	return curSize;
}

template <class T>
void LinkedList<T>::pop(const T& elem)
{
	//this function is supposed to find the node before the one that we are looking for
	//reallocate it's nodes "next" pointer to the element that is after the one that we want to delete
	//then we shrink it's size
}

#endif //LINKED_LIST_HEADER_INCLUDED
