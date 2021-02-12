#pragma once

struct Record {
	char name[30];
	short department;
	char position[22];
	char birth[10];

	bool operator==(const Record&);
	bool operator!=(const Record&);

	bool operator>(const Record&);
	bool operator<(const Record&);
};

template<typename T>
struct Node {
	T* data{0};
	Node<T>* next{0};
};

template<typename T>
struct List {
	List<T>* previous{0};
	T* data{0};
	List<T>* next{0};
};

struct Queue {
public:
	using Size = unsigned short;
	using Type = Record;
	using Tnode = Node<Type>;
	void pop();
	void push(Type*);
	Size size();

	Type* front();
	Type* back();
	Tnode* data();
	
	Queue();
	~Queue();

private:
	Tnode* first{};
	Tnode* last{};
	Size psize = 0;
};
