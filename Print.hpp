#pragma once
#include "DataStructs.hpp"

namespace Printer {
	using Count = short unsigned;
	void printRecord(Record*);
	void printBase(const List*, const Count = 20);
}

#include "Fixes.hpp"
void print_stak(Queue*);
void LorR(Vertex*&, Vertex*&);
void LorL(Vertex*&, Vertex*&);
void print_Btree(Vertex*&);
