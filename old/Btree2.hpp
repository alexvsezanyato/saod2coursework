#pragma once
#include "DataStructs.hpp"

struct Btree {
public:
	using Size = unsigned short;
	using Id = unsigned short;
	using Data = Record;

	struct Vertex {
		Size size = 0;
		List<Data>* data{0};
		List<Vertex>* childs{0};
		Vertex* parent{0};
		void insert(Data*);
	};

private:
	Size size = 0;
	Size max = 0;
	Vertex* root{0};
	bool insert(Data*, Vertex*);

public:
	bool insert(Data*);
	List<Data>* search(short department);

	Btree(short max);
	~Btree();
};