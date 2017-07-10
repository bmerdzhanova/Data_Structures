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
#ifndef DYNAMIC_ARRAY_HEADER_INCLUDED
#define DYNAMIC_ARRAY_HEADER_INCLUDED

#include <iostream>

template <class T>
class DynamicArray
{
private:
	T*data;
	size_t curSize;
	size_t capacity;
	bool isSorted;

public:
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray<T>&);
	DynamicArray<T>& operator=(const DynamicArray<T>&);
private:
	void copy(const DynamicArray<T>&);
	void clean();
public:
	void resize(size_t NewSize);

	void pushBack(const T&);
	void setAt(size_t, const T&);
	const T& getAt(size_t pos) const;
	const T& operator[](size_t) const;
	T& operator[](size_t);

	size_t getSize() const;
	size_t getCapacity() const;
	void sorted();
};


template <class T>
DynamicArray<T>::DynamicArray()
{
	data = nullptr;
	curSize = 0;
	capacity = 0;
	isSorted = false;
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
	clean();
}

template <class T>
void DynamicArray<T>::copy(const DynamicArray<T>& t)
{
	clean();

	data = new T[t.curSize];

	for (int i = 0; i < t.curSize; i++)
	{
		data[i] = t[i];
	}

	curSize = t.curSize;
	capacity = t.capacity;
	isSorted = t.isSorted;
}

template <class T>
void DynamicArray<T>::clean()
{
	delete[] data;

	data = nullptr;
	curSize = 0;
	capacity = 0;
	isSorted = false;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& t)
{
	copy(t);
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& t)
{
	if (this != &t)
	{
		clean();
		copy(t);
	}
	return *this;
}

template <class T>
void DynamicArray<T>::resize(size_t NewCap)
{
	T* tmp = data;

	data = new T[NewCap];
	for (int i = 0; i < curSize; i++)
	{
		data[i] = tmp[i];
	}

	capacity = NewCap;

	delete[] tmp;
}

template <class T>
void DynamicArray<T>::pushBack(const T& el)
{
	if (curSize >= capacity)
	{
		size_t NewCap = (capacity == 0 ? 2 : capacity * 2);
		resize(NewCap);
	}
	curSize++;
	data[curSize-1] = new T(el);
}

template <class T>
void DynamicArray<T>::setAt(size_t pos, const T& el)
{
	if (pos >= curSize)
	{
		throw std::out_of_range;
	}

	data[pos] = new T(el);
}

template <class T>
const T& DynamicArray<T>::getAt(size_t pos) const
{
	/*if (pos >= CurSize)
		throw std::out_of_range;*/

	return data[pos];
}

template <class T>
const T& DynamicArray<T>::operator[](size_t pos) const
{
	return data[pos];
}

template <class T>
T& DynamicArray<T>::operator[](size_t pos)
{
	/*if (pos >= CurSize)
		throw std::out_of_range;*/

	return data[pos];
}

template <class T>
size_t DynamicArray<T>::getSize() const
{
	return curSize;
}

template <class T>
size_t DynamicArray<T>::getCapacity() const
{
	return capacity;
}

template <class T>
void DynamicArray<T>::sorted()
{
	isSorted = true;
}
#endif //DYNAMIC_ARRAY_HEADER_INCLUDED
