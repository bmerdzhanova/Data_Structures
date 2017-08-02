#ifndef LINKED_STACK_HEADER_INCLUDED
#define LINKED_STACK_HEADER_INCLUDED
#include <iostream>

template <typename T>
class LinkedStack
{
public:
	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack& operator=(const LinkedStack&);
	~LinkedStack();

private:
	void copy(const LinkedStack&);
	void clean();

public:
	void push(const T&);
	void pop();

	bool isEmpty() const;
	size_t getSize() const;

	T& peek();
	const T& peek() const;

private:
	struct node
	{
		T data;
		node* next;

		/*node(T _data, node* _next = nullptr)
		{
			data = _data;
			next = _next;
		}*/
	};
	node* head;
	size_t curSize;
};

#endif //LINKED_STACK_HEADER_INCLUDED

template<typename T>
inline LinkedStack<T>::LinkedStack():curSize(0),head(nullptr)
{
	/*...*/
}

template<typename T>
inline LinkedStack<T>::LinkedStack(const LinkedStack & other)
{
	copy(other);
}

template<typename T>
inline LinkedStack<T> & LinkedStack<T>::operator=(const LinkedStack & other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

template<typename T>
inline LinkedStack<T>::~LinkedStack()
{
	clean();
}

template<typename T>
inline void LinkedStack<T>::copy(const LinkedStack & other)
{
	if (other.isEmpty())
		return;

	try
	{
		head = new node(other.head->data);

		node* ours = head;
		node* theirs = other.head->next;

		while (theirs != nullptr)
		{
			ours->next = new node;
			ours = ours->next;
			ours->data = theirs->data;
			ours->next = nullptr;
			theirs = theirs->next;
		}

		curSize = other.curSize;
	}
	catch (std::bad_alloc&)
	{
		clean();
		throw;
	}
}

template<typename T>
inline void LinkedStack<T>::clean()
{
	node* temp;

	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	curSize = 0;
}

template<typename T>
inline void LinkedStack<T>::push(const T & elem)
{
	node* newElement = new node;
	newElement->data = elem;
	newElement->next = head;

	head = newElement;

	curSize++;
}

template<typename T>
inline void LinkedStack<T>::pop()
{
	if (isEmpty())
		throw std::exception("Stack is empty!");

	node* temp = head;

	head = head->next;

	delete temp;

	curSize--;
}

template<typename T>
inline bool LinkedStack<T>::isEmpty() const
{
	return curSize == 0;
}

template<typename T>
inline size_t LinkedStack<T>::getSize() const
{
	return curSize;
}

template<typename T>
inline T & LinkedStack<T>::peek()
{
	if (isEmpty())
		throw std::exception("Stack is empty!");

	return head->data;
}

template<typename T>
inline const T & LinkedStack<T>::peek() const
{
	if (isEmpty())
		throw std::exception("Stack is empty!");

	return head->data;
}
