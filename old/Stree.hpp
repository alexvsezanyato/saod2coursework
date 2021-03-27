#pragma once
#include "DataStructs.hpp"
#include "Tree.hpp"

class Stree: public Tree {
public:
	using Size = unsigned short;
	using Data = Record;
	using Sindex = short;
	using Tnode = Node<Data>;

	struct Vertex {
		Data* data{nullptr};
		Vertex* left{0};
		Vertex* right{0};
	};

	void insert(Data*);
	void drop();
	Tnode* find(Sindex);
	void make(Queue* queue);
	Vertex* get();
	Size getSize();
	~Stree();

private:
	void set(Vertex*, Data*);
	void drop(Vertex*);
	Size size = 0;
	Vertex* root = nullptr;
};
