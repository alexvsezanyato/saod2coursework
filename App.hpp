#pragma once
#include "Database.hpp"
#include "Btree-fixed.hpp"

class App {
private:
	using Request = char;
	using Id = Database::Id;
	using Record = Database::Trecord;
	using Records = std::vector<Record*>;
	using Queue = Database::Tqueue;

	// deprecated,
	// but is used in ohter methods:
	Database* database = nullptr;
	void printDatabase();

public:
	void set(Database*);
	void print(Database*);
	void print(Queue*);
	bool printDatabase(Id from, Id to);
	void print(Id, Record*);
	void print(Record*);
	void print(Btree<Record*>*);
	void help();
	void warning(const char[] = nullptr);

	void clearScreen();
	void printMenu();
	App();
};
