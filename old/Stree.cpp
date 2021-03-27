#include "All.hpp"
#include "Stree.hpp"
#include "App.hpp"
#include <iostream>
#include <iomanip>

//
// ::Stree

void Stree::make(Queue* queue) {
 	for (auto node = queue->data(); node; node = node->next) {
		insert(node->data);
		continue;
	}
	return;
}

Stree::Vertex* Stree::get() {
	auto root = this->root;
	return root;
}

Stree::Size Stree::getSize() {
	auto size = this->size;
	return size;
}

void Stree::insert(Stree::Data* data) {
	if (root) {
		for (auto node = root; true;) {
			if (*data > *node->data) {
				if (node->right) {
					node = node->right;
					continue;
				}
				else {
					node->right = new Vertex;
					set(node->right, data);
					continue;
				}
			}
			else {
				if (node->left) {
					node = node->left;
					continue;
				}
				else {
					node->left = new Vertex;
					set(node->left, data);
					continue;
				}
			}
		}
	}
	else {
		root = new Vertex{
			.data = data
		};
	}
	return;
}

void Stree::set(Vertex* vertex, Data* data) {
	vertex->data = data;
	size++;
	return;
}

void Stree::drop(Stree::Vertex* node) {
	if (!node) return;
	drop(node->right);
	drop(node->left);
	delete node;
}

void Stree::drop() {
	drop(root);
	return;
}

Stree::Tnode* Stree::find(Stree::Sindex key) {
	Stree::Tnode* node = nullptr;
	Vertex* vertex = root;

	/*
	for (auto vertex = root; vertex;) {
		if (*vertex->data == key) {
			Stree::Tnode* helper = new Stree::Node;
			helper->data = vertex->data;
			helper->next = node;
			node = helper;
		}
		if (*vertex->data > key) vertex = vertex->right;
		else vertex = vertex->left;
	}
	*/
	return node;
}

Stree::~Stree() {
	if (root) drop();
	return;
}
