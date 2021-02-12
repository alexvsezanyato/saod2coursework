#include "All.hpp"
#include "Stree.hpp"

//
// ::Stree

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
					node->right->data = data;
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
					node->left->data = data;
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
	return node;
}
