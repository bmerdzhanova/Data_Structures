#ifndef DYNAMIC_STACK_INCLUDED
#define DYNAMIC_STACK_INCLUDED

template <class T>
class DynamicStack
{
private:
	struct node
	{
		T value;
		node* next;
	};

	node* top;
	int Size;

public:
	DynamicStack();
	~DynamicStack();

	void push(T);
	void pop(T&);
	T& peek();
	bool isEmpty();
};

template <class T>
DynamicStack<T>::DynamicStack()
{
	top = NULL;
	Size = 0;
}


template <class T>
DynamicStack<T>::~DynamicStack()
{
	node *nodePtr, *nextNode;

	nodePtr = top;
	
	while (nodePtr != 0)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

template <class T>
void DynamicStack<T>::push(T num)
{
	node* newNode;
	newNode = new node;
	newNode->value = num;

	if (isEmpty())
	{
		top = newNode;
		newNode->next = 0;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
	Size++;
}

template <class T>
void DynamicStack<T>::pop(T& num)
{
	node* temp;

	if (isEmpty())
	{
		std::cout << "Empty stack" << std::endl;
	}
	else
	{
		num = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
	Size--;
}

template <class T>
T& DynamicStack<T>::peek()
{
	if (!isEmpty())
		return top->value;
}

template <class T>
bool DynamicStack<T>::isEmpty()
{
	if (!top) return true;
	else return false;
	return false;
}

#endif //DYNAMIC_STACK_INCLUDED
