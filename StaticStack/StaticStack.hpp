#pragma once

template <typename TYPE, int MAX_SIZE>
class StaticStack {
private:
	TYPE data[MAX_SIZE];
	size_t Size;
public:
	StaticStack();

	void Push(const TYPE & Element);
	bool Pop(TYPE& Element);
	TYPE& Peek();
	void RemoveAll();

	size_t GetSize() const;
	size_t GetMaxSize() const;
	bool IsEmpty() const;
};

template <typename TYPE, int MAX_SIZE>
StaticStack<TYPE, MAX_SIZE>::StaticStack()
{
	Size = 0;
}

template <typename TYPE, int MAX_SIZE>
void StaticStack<TYPE, MAX_SIZE>::Push(const TYPE& el)
{
	if (Size < MAX_SIZE)
	{
		data[Size++] = el;
	}
}

template <typename TYPE, int MAX_SIZE>
bool StaticStack<TYPE, MAX_SIZE>::Pop(TYPE& el)
{
	if (Size > 0)
	{
		el = data[--Size];
		return true;
	}
	return false;
}

template <typename TYPE, int MAX_SIZE>
TYPE& StaticStack<TYPE, MAX_SIZE>::Peek()
{
	if (Size > 0)
	{
		return data[Size - 1];
	}
}

template <typename TYPE, int MAX_SIZE>
void StaticStack<TYPE, MAX_SIZE>::RemoveAll()
{
	Size = 0;
}

template <typename TYPE, int MAX_SIZE>
size_t StaticStack<TYPE, MAX_SIZE>::GetSize() const
{
	return Size;
}

template <typename TYPE, int MAX_SIZE>
size_t StaticStack<TYPE, MAX_SIZE>::GetMaxSize() const
{
	return MAX_SIZE;
}

template <typename TYPE, int MAX_SIZE>
bool StaticStack<TYPE, MAX_SIZE>::IsEmpty() const
{
	return Size == 0;
}