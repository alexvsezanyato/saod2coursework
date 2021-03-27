#pragma once
#include "DataStructs.hpp"

namespace Printer {
	using Count = short unsigned;
	using Data = Record;
	void printRecord(Data*);
	void printBase(const List<Data>*, const Count = 20);
}
