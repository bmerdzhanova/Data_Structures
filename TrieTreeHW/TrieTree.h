#ifndef TRIE_TREE_HEADER_INCLUDED
#define TRIE_TREE_HEADER_INCLUDED

const int ALPHABET_SIZE = 26;
#define CASE 'a'

struct node
{
	char symbol;
	node* nodes[ALPHABET_SIZE];
	bool isEnd = false;
	int value;
	node(char _symbol = '\0', node* _nodes[ALPHABET_SIZE] = nullptr, bool _isEnd = false, int _value = 0)
	{
		symbol = _symbol;
		if (!_nodes)
			for (int i = 0; i < ALPHABET_SIZE; i++)
				nodes[i] = nullptr;
		else
			for (int i = 0; i < ALPHABET_SIZE; i++)
				nodes[i] = _nodes[i];
		isEnd = _isEnd;
		value = _value;
	}
};

class TrieTree
{
public:
	TrieTree();
	TrieTree(const TrieTree&);
	TrieTree& operator=(const TrieTree&);
	~TrieTree();
	
	void insert(const char*, int);
	node* search(node*,const char*);

	node* getRoot() const;
	int getHeight() const;
private:
	void copy(const TrieTree&);
	void destroy(node*&);
	void copyTree(node*&, node*);

private:
	node* root;
	int height;
};

#endif //TRIE_TREE_HEADER_INCLUDED