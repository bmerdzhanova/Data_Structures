#ifndef DYNAMIC_ARRAY_HEADER_INCLUDED
#define DYNAMIC_ARRAY_HEADER_INCLUDED

#include<iostream>

template<class T>
class DynamicArray {

private:

	T *data;
	size_t CurSize;
	size_t Capacity;
	bool isSorted;

public:

	//THE BIG FOUR
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray<T>&);
	DynamicArray<T>& operator=(const DynamicArray<T>&);

	void CopyFrom(const DynamicArray<T>&);
	void Free();
	void Resize(size_t NewSize);

	void PushBack(const T&);
	const T& GetAt(size_t)const;
	void SetAt(size_t, const T&);
	const T& operator[](size_t)const;
	T& operator[](size_t);

	size_t GetSize()const;
	size_t GetCapacity()const;

	void PrintInfo()const;
	void sort();
	int Search(const T&);
private:
	int Binary(const T&);
	int Linear(const T&);
};

template<class T>
DynamicArray<T>::DynamicArray() :data(nullptr), CurSize(0), Capacity(0), isSorted(false) {

	/*...*/
}



template<class T>
DynamicArray<T>::~DynamicArray() {
	Free();
}

template<class T>
void DynamicArray<T>::Free() {

	delete[] data;

	data = nullptr;
	CurSize = 0;
	Capacity = 0;
	isSorted = false;
}

template<class T>
void DynamicArray<T>::CopyFrom(const DynamicArray<T> &other) {

	Free();

	data = new T[other.CurSize];

	//memcpy(data, other.data, sizeof(T)*other.CurSize);

	for (int i = 0; i < other.CurSize; i++) {

		data[i] = other.data[i];
	}

	CurSize = other.CurSize;
	Capacity = other.Capacity;
	isSorted = other.isSorted;

}
template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other) :data(nullptr), CurSize(0), Capacity(0) {

	CopyFrom(other);

}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &other) {

	if (this != &other) {

		CopyFrom(other);

	}

	return *this;

}

template<class T>
void DynamicArray<T>::Resize(size_t NewCap) {


	T *temp = data;

	data = new T[NewCap];

	for (int i = 0; i < CurSize; i++) {

		data[i] = temp[i];
	}

	Capacity = NewCap;

	delete[] temp;
}

template<class T>
void DynamicArray<T>::PushBack(const T& elem) {

	if (CurSize >= Capacity) {

		size_t NewCap = (Capacity == 0 ? 2 : Capacity * 2);
		Resize(NewCap);
	}

	data[CurSize++] = elem;

}


template<class T>
void DynamicArray<T>::SetAt(size_t pos, const T& elem) {


	if (pos >= CurSize) {

		throw std::out_of_range;

	}

	data[pos] = elem;

}

template<class T>
const T& DynamicArray<T>::GetAt(size_t pos)const {

	if (pos >= CurSize) {

		throw std::out_of_range("out of range!!!");

	}

	return data[pos];
}

template<class T>
const T& DynamicArray<T>::operator[](size_t pos)const {


	GetAt(pos);
}

template<class T>
T& DynamicArray<T>::operator[](size_t pos) {

	if (pos >= CurSize) {
		throw std::out_of_range("out of range!!!");
	}

	return data[pos];
}

template<class T>
size_t DynamicArray<T>::GetSize()const {

	return CurSize;
}

template<class T>
size_t DynamicArray<T>::GetCapacity()const {

	return Capacity;
}


template<class T>
void DynamicArray<T>::PrintInfo()const {

	std::cout << "obj at: Ox" << this
		<< " buffer starts at: Ox" << data
		<< " length:" << CurSize
		<< " capacity:" << Capacity << std::endl;

}

template<class T>
inline inline void DynamicArray<T>::sort()
{
	if (data)
	{
		for (int j = 1; j < CurSize; j++)
		{
			int key = data[j];
			int i = j - 1;
			while (i >= 0 && data[i]>key)
			{
				data[i + 1] = data[i];
				i = i - 1;
			}
			data[i + 1] = key;
		}
	}
	isSorted = true;
}

template<class T>
inline int DynamicArray<T>::Search(const T & t)
{
	if (isSorted)
	{
		return Binary(t);
	}
	else
	{
		return Linear(t);
	}

	return -1;
}

template<class T>
inline int DynamicArray<T>::Binary(const T & d) //0,1,2,6,8,9
{
	T left = 0, right = CurSize-1, mid;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (d == data[mid])
			return mid;
		else if (d > data[mid])
			left = mid;
		else
			right = mid;
	}
	return -1;
}

template<class T>
inline int DynamicArray<T>::Linear(const T & d)
{
	for (int i = 0; i < CurSize; i++)
	{
		if (d == data[i])
			return i;
	}
	return -1;
}
#endif //DYNAMIC_ARRAY_HEADER_INCLUDED
