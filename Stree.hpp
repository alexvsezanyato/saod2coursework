#pragma once
#include "DataStructs.hpp"

class Stree {
public:
	using Size = unsigned short;
	using Data = Record;
	using Sindex = short;
	using Node = Node<Data>;

	struct Vertex {
		Data* data{0};
		Vertex* left{0};
		Vertex* right{0};
	};

	void insert(Data*);
	void drop();
	Node* find(Sindex);

private:
	void drop(Vertex*);
	Size size = 0;
	Vertex* root = nullptr;
};