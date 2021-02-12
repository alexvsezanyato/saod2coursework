#include "All.hpp"
#include "DataStructs.hpp"
// using Size = Queue::Size;
// using Type = Queue::Type;

bool Record::operator==(const Record& record) {
	auto a = record.department;
	auto b = this->department;
	bool result = false;

	if (a == b) result = true;
	else result = false;
	return result;
}

bool Record::operator!=(const Record& record) {
	auto a = record.department;
	auto b = this->department;
	bool result = false;

	if (a != b) result = true;
	else result = false;
	return result;
}

bool Record::operator<(const Record& record) {
	auto a = this->department;
	auto b = record.department;
	bool result = false;

	if (a < b) result = true;
	else result = false;
	return result;
}

bool Record::operator>(const Record& record) {
	auto a = this->department;
	auto b = record.department;
	bool result = false;

	if (a > b) result = true;
	else result = false;
	return result;
}

Queue::Size Queue::size() {
	Size size = this->psize;
	return size;
}

Queue::Type* Queue::front() {
	Tnode* first = this->first;
	return first->data;
}

Queue::Type* Queue::back() {
	Tnode* last = this->last;
	return last->data;
}

Queue::Tnode* Queue::data() {
	auto root = this->first;
	return root;
}

void Queue::push(Type* record) {
	Tnode* node = new Tnode;
	node->data = record;
	node->next = first;
	first = node;
	psize++;
	return;
}

void Queue::pop() {
	if (!size()) return;
	Tnode* helper = this->first;
	this->first = helper->next;
	delete helper;
	psize--;
}

Queue::Queue() {
	// the queue doesn't allow set first, last
	// you can only push / pop your data
	return;
}

Queue::~Queue() {
	// nodes be droped here
	while (size()) pop();
	return;
}
