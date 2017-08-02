#ifndef DYNAMIC_ARRAY_HEADER_INCLUDED
#define DYNAMIC_ARRAY_HEADER_INCLUDED
#include <iostream>

template <typename T>
class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(const DynamicArray&);
	DynamicArray& operator=(const DynamicArray&);
	~DynamicArray();

private:
	void copy(const DynamicArray&);
	void free();
	void resize(size_t );
	int BinarySearch(const T&, size_t, size_t) const;
	int LinearSearch(const T&) const;

public:
	void pushBack(const T&);
	void popBack();

	const T& getAt(size_t) const;
	void setAt(size_t, const T&);
	const T& operator[](size_t) const;
	T& operator[](size_t);

	size_t getSize() const;
	size_t getCapacity() const;

	int search(const T&) const;

	void sort();

	void printElements() const;
private:
	T* data;
	size_t size;
	size_t capacity;

	bool isSorted;
};

#endif // DYNAMIC_ARRAY_HEADER_INCLUDED

template<typename T>
inline DynamicArray<T>::DynamicArray():data(nullptr),size(0),capacity(0)
{
	/*...*/
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray & other)
{
	copy(other);
}

template<typename T>
inline DynamicArray<T> & DynamicArray<T>::operator=(const DynamicArray & other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
	free();
}

template<typename T>
inline void DynamicArray<T>::copy(const DynamicArray & other)
{
	data = new T[other.capacity];

	for (int i = 0; i < other.size; i++)
		data[i] = other.data[i];

	size = other.size;
	capacity = other.capacity;
	isSorted = other.isSorted;
}

template<typename T>
inline void DynamicArray<T>::free()
{
	delete[] data;

	data = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
inline void DynamicArray<T>::resize(size_t newCapacity)
{
	T* tmp = new T[size];
	for (int i = 0; i < size; i++)
		tmp[i] = data[i];

	delete[] data;

	data = new T[newCapacity];

	for (int i = 0; i < size; i++)
		data[i] = tmp[i];

	capacity = newCapacity;
	delete[] tmp;
}

template<typename T>
inline int DynamicArray<T>::BinarySearch(const T & el, size_t left, size_t right) const
{
	if (left >= right)
		return -1;

	size_t middle = (right - left) / 2;

	if (el == data[middle])
		return middle;
	else if (el < data[middle])
		return BinarySearch(el, left, middle - 1);
	else if (el > data[middle])
		return BinarySearch(el, middle + 1, right);

}

template<typename T>
inline int DynamicArray<T>::LinearSearch(const T &) const
{
	for (int i = 0; i < size; i++)
		if (data[i] == el)
			return i;
	return -1;
}

template<typename T>
inline void DynamicArray<T>::pushBack(const T & el)
{
	if (size >= capacity)
	{
		size_t newCap = (capacity == 0 ? 2 : capacity * 2);
		resize(newCap);
	}
	
	data[size++] = el;
	isSorted = false;
}

template<typename T>
inline void DynamicArray<T>::popBack()
{
	if (size)
		size--;
	else
		throw std::exception("Array empty!");

	if (size * 2 <= capacity)
	{
		size_t newCap = size * 2;
		resize(newCap);
	}
}

template<typename T>
inline const T & DynamicArray<T>::getAt(size_t pos) const
{
	if (pos >= capacity)
		throw std::out_of_range;

	return data[pos];
}

template<typename T>
inline void DynamicArray<T>::setAt(size_t pos, const T & el)
{
	if (pos >= capacity)
		throw std::out_of_range;

	data[pos] = el;
}

template<typename T>
inline const T & DynamicArray<T>::operator[](size_t pos) const
{
	if (pos >= capacity)
		throw std::out_of_range;

	return data[pos];
}

template<typename T>
inline T & DynamicArray<T>::operator[](size_t pos)
{
	/*if (pos >= capacity)
		throw std::out_of_range;*/

	return data[pos];
}

template<typename T>
inline size_t DynamicArray<T>::getSize() const
{
	return size;
}

template<typename T>
inline size_t DynamicArray<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
inline int DynamicArray<T>::search(const T & el) const
{
	if (isSorted)
		BinarySearch(el, 0, size);
	else
		LinearSearch(el);
}

template<typename T>
inline void DynamicArray<T>::sort()
{
	for (int i = 1; i < size; i++)
		for (int j = i; j >= 1; j--)
			if (data[j] < data[j - 1])
				std::swap(data[j], data[j - 1]);

	isSorted = true;
}

template<typename T>
inline void DynamicArray<T>::printElements() const
{
	for (int i = 0; i < size; i++)
		cout << "arr[" << i << "]= " << data[i] << std::endl;
}
