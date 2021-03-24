#pragma once

struct Record {
	static const short nlength = 30; // 48
	static const short plength = 22; // ?
	static const short blength = 10; // ?

	char name[nlength];
	// char department[2];
	short department;
	char position[plength];
	char birth[blength];

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
