#include "All.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Database.hpp"

using std::ios;
using Id = Database::Id;
using Size = Database::Size;

bool Database::read(char* fname) {
	std::fstream fin;
	fin.open(fname, ios::in | ios::binary);

	if (!fin) {
		std::cout << "Cannot open file \"" << fname << "\".\n";
		fin.close();
		return false;
	}

	while (true) {
		Record* record = new Record;
		fin.read((char*)record, sizeof(Record));
		if (!fin.eof()) push(record);
		else break;
	}
	fin.close();
	return true;
}

void Database::push(Record* record) {
	this->records.push_back(record);
	return;
}

void Database::drop() {
	for (auto i : records) delete i;
	return;
}

Size Database::size() {
	Size size = (Size) records.size();
	return size;
}

Record* Database::at(Id id) {
	Record* record = records.at(id);
	return record;
}

void Database::copyTo(Database*& database) {
	database = new Database;
	database->records = this->records;
	return;
}

void Database::sort() {
	if (this->sorted) return;
	// .. db sorts here
	Id from = 0;
	Id to = (Id) records.size() - 1;
	Sort::sort(&this->records);
	sorted = true;
	return;
}

void Database::search(SearchSets sets) {
	auto output = sets.outputTo;
	auto key = sets.searchKey;
	while (output->size()) output->pop();
	if (!sorted) return;

	Search searchBox(
		Search::Sets{
			.what = sets.searchKey,
			.searchIn = records.data(),
			.withSize = (Size) records.size(),
			.outputTo = output,
		}
	);

	// it uses a queue point
	// and adds its data to the queue
	searchBox.search();
	return; // makeBtree(output);
}

void Database::swap(Id a, Id b) {
	auto temporary = this->at(a);
	records.at(a) = at(b);
	records.at(b) = temporary;
	return;
}

Database::~Database() {
	this->drop();
	return;
}
