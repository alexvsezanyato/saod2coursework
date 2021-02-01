#pragma once
#include <iostream>

template <typename T>
class QuickSort {
public:
	using Size = unsigned short;
	using Id = unsigned short;
	static void sort(T* data);

private:
	T* data = nullptr;
	Size size = 0;
	void sort(Id from, Id to);
	QuickSort(T* data, Size size);
	~QuickSort();
};

// .tpp files include template declaration
// templates have to be implemented in the header file
// #include "QuickSort.tpp"

template <typename T>
void QuickSort<T>::sort(T* data) {
	Size size = (Size) data->size();
	auto instance = new QuickSort(data, size);
	Id from = 0;
	Id to = (Id) size - 1;
	instance->sort(from, to);
	delete instance;
	return;
}

template <typename T>
void QuickSort<T>::sort(Id from, Id to) {
	auto pivot = this->at((from + to) / 2);
	Id i = from;

	for (Id j = from; j < to - 1; j++) {
		if (data.at(j) < pivot) {
			// swap
			auto helper = data.at(i);
			data.at(i) = data.at(j);
			data.at(j) = helper;
			// inc
			i++;
		}
	}

	// swap
	auto h = data.at(i);
	data.at(i) = data.at(to);
	data.at(to) = h;
	return;
}

template <typename T>
QuickSort<T>::QuickSort(T* data, Size size) {
	// just use class member "data", 
	// don't push it to sort methods
	this->data = data;
	this->size = size;
	return;
}

template <typename T>
QuickSort<T>::~QuickSort() {
	// no memory allocation now
	// so we do nothing here
	return;
}