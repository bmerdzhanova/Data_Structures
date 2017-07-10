#pragma once
#include <iostream>

template <class T>
class Queue
{
private:
	struct node
	{
		T data;
		node* next;

		node(const T& d, node* n = nullptr)
		{
			data = d;
			next = n;
		}
	};
	size_t curSize;
	node* pFirst;
	node* pTail;
public:
	Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();
private:
	void Copy(const Queue&);
	void Clean();
public:
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	void enqueue(const T& data);
	void dequeue();

	size_t getSize() const;
	bool isEmpty() const;
};


template <class T>
Queue<T>::Queue()
{
	pFirst = nullptr;
	pTail = nullptr;
	curSize = 0;
}

template <class T>
Queue<T>::Queue(const Queue& other)
{
	Copy(other);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
	if (this != &other)
	{
		Clean();
		Copy(other);
	}
	return *this;
}

template <class T>
Queue<T>::~Queue()
{
	Clean();
}

template <class T>
void Queue<T>::Copy(const Queue& other)
{
	if (other.isEmpty())
		return;
	try
	{
		pFirst = new node(other.pFirst->data);
		node* copy = other.pFirst;
		node* copier = pFirst;

		while (copy->next != 0)
		{
			copy = copy->next;
			copier->next = new node(copy->data);
			copier = copier->next;
		}

		pTail = copier;
		curSize = other.curSize;
	}
	catch (std::bad_alloc &) {

		Clean();
		throw;
	}
}

template <class T>
void Queue<T>::Clean()
{
	node* destroy;

	while (pFirst != nullptr)
	{
		destroy = pFirst;
		pFirst = pFirst->next;
		delete destroy;
	}

	pTail = nullptr;
	pFirst = nullptr;
	curSize = 0;
}

template <class T>
T& Queue<T>::front()
{
	if (isEmpty())
		throw std::exception("Empty!");
	return pFirst->data;
}

template <class T>
const T& Queue<T>::front() const
{
	if (isEmpty())
		throw std::exception("Empty!");
	return pFirst->data;
}


template <class T>
T& Queue<T>::back()
{
	if (isEmpty())
		throw std::exception("Empty!");
	return pTail->data;
}

template<class T>
const T& Queue<T>::back() const
{
	if (isEmpty())
		throw std::exception("Empty!");
	return pTail->data;
}

template <class T>
void Queue<T>::enqueue(const T& data)
{
	if (isEmpty())
	{
		pFirst = new node(data);
		pTail = pFirst;
		curSize++;
		return;
	}

	node* newEl = new node(data);

	pTail->next = newEl;
	pTail = pTail->next;
	curSize++;
}

template <class T>
void Queue<T>::dequeue()
{
	if (isEmpty())
		throw std::exception("Empty!");

	node* destroy = pFirst;
	pFirst = pFirst->next;
	delete destroy;
	curSize--;
}

template <class T>
bool Queue<T>::isEmpty() const
{
	return curSize == 0;
}

template <class T>
size_t Queue<T>::getSize() const
{
	return curSize;
}
