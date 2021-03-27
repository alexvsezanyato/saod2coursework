#pragma once
#include <utility>

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
	bool (*less)(T, T);
	// 1-st: the minimum degree of the tree
	// 2-nd: the tree's key-comparison function
	// 3-rd: a function that prints keys
	Btree(unsigned, bool (*)(T, T), void (*)(T) = 0);
	Btree(bool (*)(T, T), void (*)(T) = 0);
	void insert(T);
    void make(Queue *queue);
    bool empty();
	void search(Key);
	void print();
	~Btree<T>();

private:
	void search(Key, Bnode<T>*);
	void initializeNode(Bnode<T>*);
	void cut(Bnode<T>*);
	unsigned nodeInsert(Bnode<T>*, T);
	void splitChild(Bnode<T>*, int);
	void printNode(Bnode<T>*, unsigned);

	Bnode<T> *root;
	void (*printKey)(T);
	unsigned minDegree;
};

#include "Btree-fixed.cpp"
