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
#include <iostream>
#include <fstream>
#include <stdint.h>
#include "BST.hpp"
#include "DynamicArray.h"

struct node //elements of the array I am reading the file in
{
	int key;
	char* data;
	node(int k = 0, char* d = nullptr)
	{
		key = k;
		data = d;
	}
	node(node* el)
	{
		key = el->key;
		data = el->data;
	}
};


void sort(DynamicArray<node>& arr) //functuion for sorting the array before starting to build the tree
{
	if (arr.getSize())
	{
		for (int j = 1; j < arr.getSize(); j++)
		{
			node k = arr[j];
			int i = j - 1;
			while (i >= 0 && arr[i].key > k.key)
			{
				arr[i + 1] = arr[i];
				i = i - 1;
			}
			arr[i + 1] = k;
		}
	}
	arr.sorted();
}

void buildTree(BST<char*>& myTree, int left, int right, DynamicArray<node>& arr) //builds a perfect balanced tree
{
	if (left > right)
		return;

	int mid = (left + right) / 2;

	myTree.add(arr[mid].key, arr[mid].data);

	buildTree(myTree, left, mid - 1, arr);
	buildTree(myTree, mid + 1, right, arr);
}

void readFile(char* filename, DynamicArray<node>& arr) 
{
	std::ifstream file;
	int index = 0;
	file.open(filename, std::ios::binary);
	while (!file.eof())
	{
		uint32_t a, size;
		file >> a;
		file >> size;
		char* data = new char[size + 1];
		file >> data;
		node* newNode = new node(a, data);
		arr.pushBack(newNode); // I am storing the information in an array of nodes
	}
}

void mainLoop(BST<char*>& myTree)
{
	bool check = true;
	while (check)
	{
		char* command = new char;
		std::cin >> command;
		if (strcmp(command,"add") == 0)
		{
			int key;
			char* data = new char;
			std::cin >> key >> data;
			myTree.add(key, data);

			char* answer = new char;
			std::cout << "Will you enter another command? (Yes/No)" << std::endl;
			std::cin >> answer;
			if (answer == "No")
				check = false;
		}
		else if (strcmp(command,"remove") == 0)
		{
			int key;
			char* data = new char;
			std::cin >> key >> data;
			myTree.remove(key, data); //not implemented yet

			char* answer = new char;
			std::cout << "Will you enter another command? (Yes/No)" << std::endl;
			std::cin >> answer;
			if (answer == "No")
				check = false;

		}
		else if (strcmp(command,"removeall") == 0)
		{
			int key;
			std::cin >> key;
			myTree.removeAll(key);

			char* answer = new char;
			std::cout << "Will you enter another command? (Yes/No)" << std::endl;
			std::cin >> answer;
			if (answer == "No")
				check = false;
		}
		else if (strcmp(command,"search") == 0)
		{
			int key;
			char* data = new char;
			std::cin >> key >> data;
			if (myTree.search(key, data))
				std::cout << "true" << std::endl;
			else
				std::cout << "false" << std::endl;

			char* answer = new char;
			std::cout << "Will you enter another command? (Yes/No)" << std::endl;
			std::cin >> answer;
			if (answer == "No")
				check = false;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 1)
		std::cout << "Error! You didn't enter a file name!" << std::endl;
	BST<char*> myTree;
	DynamicArray<node> arr;
	readFile(argv[1], arr);
	sort(arr);
	buildTree(myTree, 0, arr.getSize(), arr);
	mainLoop(myTree);
	return 0;
}