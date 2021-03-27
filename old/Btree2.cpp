#include "All.hpp"
#include "Tree.hpp"
#include "DataStructs.hpp"

//
// ::Btree

void Btree::Vertex::insert(Btree::Data* data) {
	for (auto i = this->data; true; i->next) {
		if (data < i->data) {
			List<Btree::Data>* node = new List<Btree::Data>;
			node->data = data;

			i->previous = node;
			node->previous = i->previous;
			node->next = i;

			if (node->previous) node->previous->next = node;
			else this->data = node;
			return;
		}

		if (!i->next) {
			List<Btree::Data>* node = new List<Btree::Data>;
			node->data = data;

			i->next = node;
			node->previous = i;
			node->next = nullptr;

			if (node->previous) node->previous->next = node;
			else this->data = node;
			return;
		}
	}
}

bool Btree::insert(Btree::Data* data, Btree::Vertex* vertex) {
	// insertion
	return true;
}

bool Btree::insert(Btree::Data* data) {
	if (!this->root) {
		// if there's no vertex in the Btree,
		// a vertex (root) must be created
		auto r = this->root;
		r = new Vertex;
		r->size = 1;
		r->data = new List<Btree::Data>;
		r->data->data = data;
		r->size++;
		return true;
	}
	auto v = this->root;

	while (true) {
		if (!v->childs) {
			if (v->size < max) {
				// the end,
				// you can insert to the vertex.
				v->insert(data);
				v->size++;
				return true;
			}
			else {
				// the end,
				// but vertex size is max
				// m - middle, r - right vertex, l - left one
				List<Btree::Data>* m{ 0 }, * r{ 0 }, * l{ 0 };

				// set middle vertex
				m = v->data;
				for (int i = 0; i < v->size / 2; i++) m = m->next;
				if (!m) return false;

				// set left & right vertexes
				r = (m->next) ? m->next : nullptr;
				l = v->data;

				// improve referencing
				if (r) r->previous = nullptr;
				if (m->previous) m->previous->next = nullptr;

				// the vertex we try to insert to
				// splits into two ones
				// so we delete the vertex
				// and create two new vertexes
				Vertex* lvertex = new Vertex;
				lvertex->data = l;
				lvertex->size = v->size / 2;

				Vertex* rvertex = new Vertex;
				rvertex->data = r;
				rvertex->size = v->size - lvertex->size - 1;



				v->data = nullptr;
				delete v;
				return true;
			}
		}
		else {
			// not the end yet,
			// go down
			auto child = v->childs;

			for (auto i = v->data; true; i->next) {
				if (data < i->data) {
					v = child->data;
					break;
				}

				if (!i->next) {
					// the last vertex item,
					// but there is a child after the item
					// so we go there
					v = child->next->data;
					break;
				}

				child = child->next;
			}
		}
	}
	return true;
}

List<Btree::Data>* Btree::search(short department) {
	auto result = nullptr;
	return result;
}

Btree::Btree(short max) {
	this->max = max;
	return;
}

Btree::~Btree() {
	// free memory here
	return;
}