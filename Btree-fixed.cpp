#pragma once
#include <cstdlib>
#include <utility>

template <typename T>
Btree<T>::Btree(bool (*compare)(T, T), void (*echo)(T)) {
	// 1: comparison function for managing elements
	// 2: `echo` prints keys.
	this->minDegree = 2;
	this->less = compare;
	this->root = new Bnode<T>;
	this->root->leaf = true;
	initializeNode(root);
	this->printKey = echo;
	return;
}

template <typename T>
Btree<T>::~Btree<T>() {
	// cut down the tree
	cut(root);
	return;
}

template <typename T>
bool Btree<T>::empty() {
	bool result;
	if (root || root->size) result = false;
	else result = true;
	return result;
}

template <typename T>
void Btree<T>::make(Queue *queue) {
	if (!queue) return;
    auto node = queue->data();

    while (true) {
        if (!node) break;
        this->insert(node->data);
        node = node->next;
    }
    return;
}

template <typename T>
void Btree<T>::insert(T e) {
	if (root->size == 2 * minDegree - 1) {
		// grow upwards if the root is full.
		// root updates to the new one.
		// old root is the 1-st child of the new one
		Bnode<T> *newRoot = new Bnode<T>;
		newRoot->leaf = false;
		initializeNode(newRoot);
		newRoot->child[0] = root;
		root = newRoot;
		splitChild(newRoot, 0);
	}

	// Work down the tree.
	Bnode<T> *node = root;

	while (!node->leaf) {
		// Find the proper child to go to.
		int i = node->size - 1;
		while (i >= 0 && less(e, node->key[i])) i--;
		i++;

		// Split child if full.
		if (node->child[i]->size == 2 * minDegree - 1) {
			splitChild(node, i);
			if (less(node->key[i], e)) i++;
		}
		node = node->child[i];
	}

	nodeInsert(node, e);
	return;
}

// Function for printing a tree.
template <typename T>
void Btree<T>::print() {
	if (printKey != NULL && root != NULL) {
		printNode(root, 0);
		printf("\n");
	}
}

template <typename T>
void Btree<T>::initializeNode(Bnode<T> *x) {
	// no size, but keys are created
	// childs = keys + 1
	x->size = 0;
	x->key = new T[2 * minDegree - 1];
	x->child = new Bnode<T>*[2 * minDegree];
	return;
}

template <typename T>
void Btree<T>::cut(Bnode<T> *node) {
	// recursively deletes the subtree
	// does the dirty work for the destructor

	if (!node->leaf)
		for (short i = 0; i <= node->size; i++) {
			cut(node->child[i]);
			continue;
		}

	delete [] node->child;
	delete [] node->key;
	delete node;
}

// Inserts k into x.
// Returns the index of k in x->key.
template <typename T>
unsigned Btree<T>::nodeInsert(Bnode<T> *x, T k) {
	int index;

	// Make room for k.
	for (index = x->size; index > 0 && less(k, x->key[index - 1]); index--) {
		x->key[index] = x->key[index - 1];
		x->child[index + 1] = x->child[index];
	}

	// Insert k.
	x->child[index + 1] = x->child[index];
	x->key[index] = k;
	x->size++;
	return index;
}

// function for splitting nodes that are too full.
// x points to the parent of the node to splits.
// i is the index in x's child array of the node to split.
template <typename T>
void Btree<T>::splitChild(Bnode<T> *x, int i) {
	// z is the new node and y is the node to split.
	Bnode<T> *toSplit = x->child[i];
	Bnode<T> *newNode = new Bnode<T>;
	initializeNode(newNode);
	newNode->leaf = toSplit->leaf;
	newNode->size = minDegree - 1;

	// Copy the second half of y's keys and children into z.
	for (unsigned j = 0; j < minDegree - 1; j++) {
		newNode->key[j] = toSplit->key[j + minDegree];
	}
	if (!toSplit->leaf) {
		for (unsigned j = 0; j < minDegree; j++) {
			newNode->child[j] = toSplit->child[j + minDegree];
		}
	}
	toSplit->size = minDegree - 1;
	nodeInsert(x, toSplit->key[minDegree - 1]);
	x->child[i + 1] = newNode;
	return;
}

template <typename T>
void Btree<T>::search(Btree::Key key) {
	std::cout << "Records (tree search): \n" << std::endl;
	search(key, root);
	std::cout << '\n';

	std::cout
		<< "{any} - go back. \n"
		<< std::endl
		<< "Your choise: ";

	std::string answer;
	std::getline(std::cin, answer);
	std::cout << '\n';
	char request;
	if (answer.size()) request = answer.at(0);
	else request = 'd';

	switch (request) {
		case 'd': default: {
			break;
		}
	}
	return;
}

template <typename T>
void Btree<T>::search(Btree::Key key, Bnode<T> *node) {
	for (short i = 0, j = 0; i < node->size; i++) {
		if (node->key[i]->department == key) {
			printKey(node->key[i]);
			continue;
		}
	}

	if (!node->leaf)
		for (short i = 0; i <= node->size; i++) {
			search(key, node->child[i]);
			continue;
		}

	// search just prints now
	// so it returns void
	return;
}


template <typename T>
void Btree<T>::printNode(Bnode<T> *node, unsigned position) {
	for (short i = 0, j = 0; i < node->size; i++) {
		std::cout << position << '.' << j++ << ": ";
		printKey(node->key[i]);
	}

	if (!node->leaf && ++position)
		for (short i = 0; i <= node->size; i++) {
			printNode(node->child[i], position);
			continue;
		}
}
