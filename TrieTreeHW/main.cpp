/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Betina Merdzhanova
* @idnumber 45151
* @task 3
* @compiler VC
*
*/

#include <iostream>
#include <fstream>
#include "TrieTree.h"

void validate(char* word)
{
	for (int i = 0; i < strlen(word);i++)
		if(word[i] >= 'A' && word[i] <= 'Z')
			word[i] += ('a' - 'A');
		else if (word[i] == '.')
			word[i] = '\0';
}

void readDictionary(TrieTree& tree, const char* fileName)
{
	char phrase[1024];
	char* finPhrase = new char[1024];
	std::ifstream file(fileName);
	if (!file)
		throw std::exception("File did not open! ");

	while (!file.eof())
	{
		file >> phrase;
		strcpy(finPhrase, phrase);
		file.seekg(+1, std::ios::cur);
		while (file.peek() >= 'a' && file.peek() <= 'z')
		{
			file >> phrase;
			strcat(finPhrase, " ");
			strcat(finPhrase, phrase);
			file.seekg(+1, std::ios::cur);
		}
		int val;
		file >> val;
		tree.insert(finPhrase, val);
	}
	file.close();
	delete[] finPhrase;
}

int evaluateFile(char* fileName, TrieTree& trie)
{
	int evaluation = 0;
	int cnt = 0;
	std::ifstream file(fileName);
	if (!file)
		throw std::exception("File did not open! ");

	char curWord[1024];
	node* curNode;
	while (!file.eof())
	{
		file >> curWord;
		validate(curWord);
		cnt++;
		curNode = trie.search(trie.getRoot(), curWord);

		while (curNode && !curNode->isEnd)
		{
			file >> curWord;
			validate(curWord);
			cnt++;
			curNode = trie.search(curNode, curWord);
		}

		if(curNode && curNode->isEnd)
		{
			node* lastCorrect;
			while (strlen(curWord) < trie.getHeight())
			{
				file >> curWord;
				validate(curWord);
				cnt++;
				lastCorrect = curNode;
				curNode = trie.search(curNode, curWord);
				if (!curNode)
				{
					curNode = lastCorrect;
					int len = strlen(curWord) + 1;
					file.seekg(-len, std::ios::cur);
					cnt--;
					break;
				}
			}			
		}
		
		if(curNode)
			evaluation += curNode->value;
	}
	
	file.close();
	return evaluation / cnt;
}

int main(int argc, char* argv[])
{
	if (argc < 2) //if the user enters under 2 file names
	{
		std::cout << "Not enough arguments!" << std::endl;
		return 1;
	}
	TrieTree tree;
	readDictionary(tree, argv[1]);

	for (int i = 2; i < argc; i++)
		std::cout << argv[i] << " " << evaluateFile(argv[i], tree) << std::endl;
	return 0;
}