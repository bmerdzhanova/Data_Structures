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
#include <iostream>
#include "LinkedList.hpp"

template <class T>
class BST
{
private:
	struct treeNode
	{
		int key;
		LinkedList<T> data; //if there are elements with the same key but with different data we use Linked list store the data
		treeNode* leftChild;
		treeNode* rightChild;
		treeNode(int k = 0, LinkedList<T> d = nullptr)
		{
			key = k;
			data = d;
			leftChild = nullptr;
			rightChild = nullptr;
		}

		treeNode(int k = 0, T d = nullptr)
		{
			key = k;
			data.pushBack(d);
			leftChild = nullptr;
			rightChild = nullptr;
		}
	};
	treeNode* root;
public:
	BST();
	BST(const BST&);
	BST& operator=(const BST&);
	~BST();
	void add(int, T); // function for adding new element in the tree
	bool search(int, T); // function for searching for an element in the tree
	void removeAll(int&); //function that removes all elements with the same key
	void remove(int&, T); //function that removes a single element with given key and data
private:
	//help functions
	void copy(treeNode*&, treeNode*&);
	void destroy(treeNode*);
	void insert(treeNode*&, int, T);
	bool found(treeNode*, int, T);
	void removeAll(treeNode*&, int&);
	void remove(treeNode*&, int&, T);
};

template <class T>
BST<T>::BST()
{
	root = nullptr;
}

template <class T>
BST<T>::BST(const BST& other)
{
	copy(root, other.root);
}

template <class T>
BST<T>& BST<T>::operator=(const BST& other)
{
	if (this != &other)
	{
		destroy(root);
		copy(root, other.root);
	}
	return *this;
}

template <class T>
BST<T>::~BST()
{
	destroy(root);
}

template <class T>
void BST<T>::copy(treeNode*& newTree, treeNode*& other)
{
	if (other == nullptr)
	{
		newTree = nullptr;
		return;
	}

	newTree = new treeNode(other->key, other->data);

	copy(newTree->leftChild, other->leftChild);
	copy(newTree->rightChild, other->rightChild);
}

template <class T>
void BST<T>::destroy(treeNode* root)
{
	if (root != nullptr)
	{
		destroy(root->leftChild);
		destroy(root->rightChild);

		delete root;
	}
}

template <class T>
void BST<T>::add(int key, T data)
{
	insert(root, key, data);
}

template <class T>
bool BST<T>::search(int key, T data)
{
	if (found(root, key, data))
		return true;
	return false;
}

template <class T>
void BST<T>::insert(treeNode*& curRoot, int key, T data)
{
	if (data)
	{
		if (!curRoot)
		{
			curRoot = new treeNode(key, data);
		}
		else
		{
			if (curRoot->key > key)
				insert(curRoot->leftChild, key, data);
			else if (curRoot->key < key)
				insert(curRoot->rightChild, key, data);
			else if (curRoot->key == key)
				curRoot->data.pushBack(data);
		}
	}
	else
		return;
}

template <class T>
bool BST<T>::found(treeNode* curRoot, int key, T data)
{
	if (!curRoot)
		return false;
	else
	{
		if (curRoot->key == key && curRoot->data.search(data))
			return true;
		else if (curRoot->key > key)
			return found(curRoot->leftChild, key, data);
		else if (curRoot->key < key)
			return found(curRoot->rightChild, key, data);
	}
	if (curRoot->leftChild == nullptr && curRoot->rightChild == nullptr)
		return false;
}

template <class T>
void BST<T>::removeAll(int& key)
{
	removeAll(root, key);	
}

template <class T>
void BST<T>::removeAll(treeNode*& root, int& key)
{
	if (!root)
		return;
	if (key < root->key)
	{
		removeAll(root->leftChild, key);
		return;
	}
	if (key > root->key)
	{
		removeAll(root->rightChild, key);
		return;
	}

	if (root->leftChild != nullptr && root->rightChild != nullptr)
	{
		treeNode* tmp = root->leftChild;

		while (tmp->rightChild != nullptr)
			tmp = tmp->rightChild;

		root->data = tmp->data;
		root->key = tmp->key;

		removeAll(root->leftChild, root->key);
	}
	else
	{
		if (root->leftChild)
		{
			root->data = root->leftChild->data;
			root->key = root->leftChild->key;
			root = root->leftChild;
		}
		if (root->rightChild)
		{
			root->data = root->rightChild->data;
			root->key = root->rightChild->key;
			root = root->rightChild;
		}
		delete root;
		root = nullptr;
	}

}

template <class T>
void BST<T>::remove(int& key, T data)
{
	remove(root, key, data);
}

template <class T>
void BST<T>::remove(treeNode*& root, int&key, T data)
{
	if (!root)
		return;
	if (key < root->key)
	{
		remove(root->leftChild, key, data);
		return;
	}
	if (key > root->key)
	{
		remove(root->rightChild, key, data);
		return;
	}

	if (root->data.search(data))
	{
		root->data.pop(data);
	}
	else
		std::cout << "false" << std::endl;
}