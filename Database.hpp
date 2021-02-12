#pragma once
#include <cstdlib>
#include <iostream>
#include "DataStructs.hpp"
// #include "Stree.hpp"
#include <vector>
#include <queue>


class Database {
public:
	using Tqueue = Queue;
	using Trecord = Record;
	using Records = std::vector<Trecord*>;
	using Size = unsigned short;
	using Id = unsigned short;
	// sort
	class QuickSort;
	using Sort = QuickSort;
	// search
	using SearchResult = std::vector<Id>;
	using SearchKey = char*;
	class BinarySearch;
	using Search = BinarySearch;
	// using Tree = Stree;

	struct SearchSets {
		SearchKey searchKey;
		Tqueue* outputTo;
	};

private:
	bool sorted = false;
	Records records;
	void push(Record*);
	void drop();

public:
	// Tree* makeTree(Tqueue*);
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
	Key getKey(Trecord*);

private:
	QuickSort(Records* data);
	void sort(Trecord*[], Size);
};

class Database::BinarySearch {
public:
	struct Sets {
		SearchKey what;
		Record** searchIn{};
		Size withSize = 0;
		Tqueue* outputTo{};
	};

private:
	SearchKey searchKey;
	Record** searchIn{};
	Size size = 0;
	Tqueue* outputTo{};
	void search(Trecord** root, Size size);

public:
	BinarySearch(Sets);
	void search();
	// char* getKey(Record*);
};
