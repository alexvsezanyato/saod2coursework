#pragma once
#include <cstdlib>
#include <iostream>
#include "DataStructs.hpp"
#include "Stree.hpp"
#include <vector>
#include <queue>


class Database {
public:
	using Queue = Queue;
	using Records = std::vector<Record*>;
	using Size = unsigned short;
	using Id = unsigned short;
	using Record = Record;
	// sort
	class QuickSort;
	using Sort = QuickSort;
	// search
	using SearchResult = std::vector<Id>;
	using SearchKey = char*;
	class BinarySearch;
	using Search = BinarySearch;
	using Tree = Stree;

	struct SearchSets {
		SearchKey searchKey;
		Queue* outputTo;
	};

private:
	bool sorted = false;
	Records records;
	void push(Record*);
	void drop();

public:
	Tree* makeTree(Queue*);
	bool read(char*);
	void sort();
	void search(SearchSets);
	void copyTo(Database*&);
	Record* at(Id);
	void swap(Id, Id);
	Size size();
	~Database();
};

class Database::QuickSort {
public:
	using Key = unsigned int;
	static void sort(Records* data);
	Records* data = nullptr;
	Key getKey(Record*);

private:
	QuickSort(Records* data);
	void sort(Record*[], Size);
};

class Database::BinarySearch {
public:
	struct Sets {
		SearchKey what;
		Record** searchIn{};
		Size withSize = 0;
		Queue* outputTo{};
	};

private:
	SearchKey searchKey;
	Record** searchIn{};
	Size size = 0;
	Queue* outputTo{};
	void search(Record** root, Size size);

public:
	BinarySearch(Sets);
	void search();
	// char* getKey(Record*);
};