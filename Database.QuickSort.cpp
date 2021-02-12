#include "All.hpp"
#include <vector>
#include <string>
#include <cctype>
#include "Database.hpp"
using Id = Database::Id;
using Size = Database::Size;
using Key = Database::Sort::Key;

void Database::QuickSort::sort(Records* data) {
	Size size = (Size) data->size();
	auto instance = new Sort(data);
	instance->sort(data->data(), data->size());
	delete instance;
	return;
}

Key Database::QuickSort::getKey(Trecord* record) {
	if (!record) exit(-1);
	Key key = 0;

	for (int i = 6; i <= 7; i++) {
		if (std::isdigit(record->birth[i])) {
			key *= 10;
			key += record->birth[i] - '0';
		}
	}

	for (int i = 3; i <= 4; i++) {
		if (std::isdigit(record->birth[i])) {
			key *= 10;
			key += record->birth[i] - '0';
		}
	}

	for (int i = 0; i <= 1; i++) {
		if (std::isdigit(record->birth[i])) {
			key *= 10;
			key += record->birth[i] - '0';
		}
	}
	// std::cout << "birth: {" << record->birth << "}; ";
	// std::cout << "key: {" << key << "} \n";
	return key;
}

void Database::QuickSort::sort(Trecord* data[], Size size) {
	int i = 0; // first id
	int j = size - 1; // last id
	Key pivot = getKey(data[size / 2]);

	do {
		while (getKey(data[i]) < pivot) {
			i++;
		}
		
		while (getKey(data[j]) > pivot) {
			j--;
		}

		// swap
		if (i <= j) {
			auto helper = data[i];
			data[i] = data[j];
			data[j] = helper;

			i++;
			j--;
		}
	} while (i <= j);

	if (j > 0) sort(data, j + 1);
	if (i < size) sort(&data[i], size - i);
}

Database::Sort::QuickSort(Records* data) {
	// just use class member "data", 
	// don't push it to sort methods
	this->data = data;
	return;
}
