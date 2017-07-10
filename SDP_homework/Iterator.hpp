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
#pragma once

template <class T>
class Iterator
{
private:
	struct node
	{
		T data;
		node* pNext;
		node(T d, node* n = nullptr)
		{
			data = d;
			pNext = n;
		}
	};
	node* pNode;
public:
	const T& operator*() const;
	T& operator*();
	const T& operator->() const;
	T& operator->();
	Iterator& operator++();
	bool operator==(const Iterator&) const;
	bool operator!=(const Iterator&) const;
	bool operator<(const Iterator&) const;
	bool operator>(const Iterator&) const;
};

template <class T>
const T& Iterator<T>::operator*() const
{
	return pNode->data;
}

template <class T>
T& Iterator<T>::operator*()
{
	return pNode->data;
}

template <class T>
const T& Iterator<T>::operator->() const
{
	return pNode->*data;
}

template <class T>
T& Iterator<T>::operator->()
{
	return pNode->*data;
}


template <class T>
Iterator<T>& Iterator<T>::operator++()
{
	pNode = pNode->pNext;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T>& other) const
{
	return pNode == other.pNode;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const
{
	return !(other == *this);
}

template <class T>
bool Iterator<T>::operator<(const Iterator<T>& other) const
{
	return pNode->data < other.pNode->data;
}

template <class T>
bool Iterator<T>::operator>(const Iterator<T>& other) const
{
	return pNode->data > other.pNode->data;
}