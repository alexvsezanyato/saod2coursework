#pragma once
#include <utility>
#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'
typedef char BTREE_EXCEPTION;

template <typename T>
struct Bnode {
	Bnode<T> **child = nullptr;
	T *key = nullptr;
	unsigned size = 0;
	bool leaf = false;
};

template <typename T>
class Btree {
public:
	using Key = short;
	// 1-st: the minimum degree of the tree
	// 2-nd: the tree's key-comparison function
	// 3-rd: a function that prints keys
	Btree(unsigned, bool (*)(T, T), void (*)(T) = 0);
	Btree(bool (*)(T, T), void (*)(T) = 0);
	void insert(T);
    void make(Queue *queue);
    static void makeFrom(Queue *queue, Btree<T> *btree);
    short getSize();
	bool (*lessThan)(T, T);
	void search(Key);
	void search(Key, Bnode<T>*);
	void print();
	~Btree<T>();

	// Removes a key from the tree.
	// Throws a BTREE_EXCEPTION if no item was found to remove.
	// Logorithmic time.
	T remove(T);

	// Function to find a key in the tree.
	// returnValue.first is the node the item is in.
	// returnValue.second is the correct index in that node's key array
	// Logorithmic time.
	std::pair<Bnode<T>*, unsigned> search(T);

	// Uses search but just returns the key rather than the whole node.
	// Useful when T is a key value pair and lessThan only looks at the key.
	// Throws a BTREE_EXCEPTION if no item matching the parameter is found
	// Logorithmic time.
	T searchKey(T);

private:

	// Used for initializing nodes.
	void initializeNode(Bnode<T>*);

	// Recursive function called by destructor.
	void freeNode(Bnode<T>*);

	// Finds the index of a key in a node.
	unsigned findIndex(Bnode<T>*, T);

	// Inserts a key into a node.
	unsigned nodeInsert(Bnode<T>*, T);

	// Deletes the key at a given index from a node.
	T nodeDelete(Bnode<T>*, unsigned);

	// Function for splitting nodes that are too full.
	void splitChild(Bnode<T>*, int);

	// Merges two children of a node at a given index into one child.
	char mergeChildren(Bnode<T>*, unsigned);

	// Makes sure the child of a node at a specified index has >= minDegree items.
	char fixChildSize(Bnode<T>*, unsigned);

	// Recursively prints a subtree.
	void printNode(Bnode<T>*, unsigned);

	Bnode<T> *root;
	void (*printKey)(T);
	unsigned minDegree;
};

#include "Btree-fixed.cpp"
