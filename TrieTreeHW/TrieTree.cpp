#include "TrieTree.h"
#include <iostream>

TrieTree::TrieTree(): root(new node), height(0)
{
	/*...*/
}

TrieTree::TrieTree(const TrieTree & other)
{
	copy(other);
}

TrieTree & TrieTree::operator=(const TrieTree & other)
{
	if (this != &other)
	{
		destroy(this->root);
		copy(other);
	}
	return *this;
}

TrieTree::~TrieTree()
{
	destroy(root);
}

void TrieTree::insert(const char * word, int val)
{
	if (strlen(word) > height)
		height = strlen(word);

	node* trie = root;

	while (*word != '\0')
	{
		if (!trie->nodes[*word - CASE] && *word != ' ')
		{
			trie->nodes[*word - CASE] = new node(*word);
			trie = trie->nodes[*word - CASE];
		}
		*word++;
	}
	trie->isEnd = true;
	trie->value = val;
}

node * TrieTree::search(node* curRoot, const char * word)
{
	node* trie = curRoot;

	while (*word != '\0')
	{
		if (trie->nodes[*word - CASE] && *word != ' ')
			trie = trie->nodes[*word - CASE];
		else
			return nullptr;
		*word++;
	}

	return trie;
}

node * TrieTree::getRoot() const
{
	return root;
}

int TrieTree::getHeight() const
{
	return height;
}

void TrieTree::copy(const TrieTree & other)
{
	copyTree(root, other.root);
	height = other.height;
}

void TrieTree::destroy(node*& tree)
{
	if (tree)
		for (int i = 0; i < ALPHABET_SIZE; i++)
			if (tree->nodes[i])
				destroy(tree->nodes[i]);

	delete tree;
}

void TrieTree::copyTree(node *& newTree, node * toCopy)
{
	if (!toCopy)
	{
		newTree = nullptr;
		return;
	}
	else
		for (int i = 0; i < ALPHABET_SIZE; i++)
			copyTree(newTree->nodes[i], toCopy->nodes[i]);
}
