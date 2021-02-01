#include "Database.hpp"
#include <cstring>

Database::BinarySearch::BinarySearch(Sets sets) {
	this->searchIn = sets.searchIn;
	this->size = sets.withSize;
	this->outputTo = sets.outputTo;
	this->searchKey = sets.what;
	return;
}

void Database::BinarySearch::search(Record** root, Size size) {
	if (!root || !size) return;
	// .. bad
	Id middle = (size - 1) / 2;

	char key[] = "00";
	key[0] = root[middle]->birth[6];
	key[1] = root[middle]->birth[7];
	int result = std::strcmp(key, searchKey);
	
	// {strcmp(a, b) > 0} => {a > b}
	if (size > 1) {
		if (!result) {
			// outputTo->push(root[middle]);
			search(root, middle + 1);
			search(&root[middle + 1], size - middle - 1);
		}

		if (result > 0) search(root, middle + 1);
		if (result < 0) search(&root[middle + 1], size - middle - 1);
	}
	else {
		if (!result) {
			outputTo->push(root[middle]);
		}
	}
	
	return;
}

void Database::BinarySearch::search() {
	search(searchIn, size);
	return;
}