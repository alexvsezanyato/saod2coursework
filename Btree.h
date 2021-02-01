/* B-Btree
 * Author:	Caleb Baker
 * Date:	10/8/17
 * Summary:	A B-Btree data structure.
 *			Most standard operations run in O(lg(n)) time.
 *			Uses O(n) memory.
 *			Where n is the number of items in the Btree.
 */


#pragma once
#include <utility>

#define NULL 0
#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'


// struct for representing nodes of a b Btree
template <typename T>
struct BNode {
	BNode<T> **child;	// Array of pointers to children.
	T *key;				// Array of keys.
	unsigned size;		// Number of keys.
	bool leaf;			// Whether the node is a leaf.
};


typedef char Btree_EXCEPTION;


// class for representing b Btrees.
template <typename T>
class Btree {
public:
	// Constructor
	// First parameter is the minimum degree of the Btree.
	// Second parameter is the Btree's key-comparison function.
	// Third parameter is a function that prints keys.
	// Constant time.
	Btree(unsigned, bool (*)(T, T), void (*)(T) = NULL);

	// Destructor.
	// Linear time.
	~Btree<T>();

	// Inserts a key into the Btree.
	// Logorithmic time.
	void insert(T);

	// Removes a key from the Btree.
	// Throws a Btree_EXCEPTION if no item was found to remove.
	// Logorithmic time.
	T remove(T);

	// Function to find a key in the Btree.
	// returnValue.first is the node the item is in.
	// returnValue.second is the correct index in that node's key array
	// Logorithmic time.
	std::pair<BNode<T>*, unsigned> search(T);

	// Uses search but just returns the key rather than the whole node.
	// Useful when T is a key value pair and lessThan only looks at the key.
	// Throws a Btree_EXCEPTION if no item matching the parameter is found
	// Logorithmic time.
	T searchKey(T);

	// Prints the Btree.
	// Linear time
	void print();

private:

	// Used for initializing nodes.
	void initializeNode(BNode<T>*);

	// Recursive function called by destructor.
	void freeNode(BNode<T>*);

	// Finds the index of a key in a node.
	unsigned findIndex(BNode<T>*, T);

	// Inserts a key into a node.
	unsigned nodeInsert(BNode<T>*, T);

	// Deletes the key at a given index from a node.
	T nodeDelete(BNode<T>*, unsigned);

	// Function for splitting nodes that are too full.
	void splitChild(BNode<T>*, int);

	// Merges two children of a node at a given index into one child.
	char mergeChildren(BNode<T>*, unsigned);

	// Makes sure the child of a node at a specified index has >= minDegree items.
	char fixChildSize(BNode<T>*, unsigned);

	// Recursively prints a suBtree.
	void printNode(BNode<T>*, unsigned);

	// Root node.
	BNode<T> *root;

	// Comparison function used for managing element placement.
	bool (*lessThan)(T, T);

	// Function used to print items in the Btree.
	void (*printKey)(T);

	// Minimum degree of the Btree.
	unsigned minDegree;
};

#include "Btree.cpp"
