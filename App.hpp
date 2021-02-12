﻿#pragma once
#include "Database.hpp"

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

	// for windows, 
	// changes encoding:
	char* echo(char*);

	void clearScreen();
	void printMenu();
	App();
};
