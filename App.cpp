#include "All.hpp"
#include <fstream>
#include <iostream>
#include "DataStructs.hpp"
#include "App.hpp"
#include "Database.hpp"
#include <string>
#include <iomanip>


void App::clearScreen() {
	// system("cls");
	return;
}

void App::printMenu() {
	std::wcout
		<< "{1}. Show records. \n"
		<< "{2}. Show sorted records. Key: birthdate. \n"
		<< "{3}. Encode & show encoding stats. \n"
		<< std::endl
		<< "{s} <birthyear, format: yy>. Search. \n"
		<< "{t} <deparment: number>. Search using the Btree of the last search result \n"
		<< "{e}. Exit \n";
	return;
}

char* App::echo(char* data) {
	const short size = 30;
	// char result[size];
	// OemToCharBuff(data, result, size);
	return data; // result;
}

void App::print(Id id, Record* record) {
	std::wcout
		<< std::setw(4)
		<< std::setfill(L'0')
		<< id
		<< ". ";
	std::wcout << record->name << " - ";
	std::wcout << record->position << " - ";
	std::wcout
		<< std::setw(3)
		<< std::setfill(L'0')
		<< record->department
		<< " - ";
	std::wcout << record->birth << '\n';
}

bool App::printDatabase(Id from, Id to) {
	if (!this->database) return false;
	auto max = this->database->size() - 1;
	if (to > max) to = max;
	if (to < 0) to = 0;
	if (from > to) from = to;
	if (from < 0) from = 0;
	//..

	for (Id id = from; id <= to; id++) {
		Record* record = database->at(id);
		if (!record) return false;
		print(id, record);
	}
	return true;
}

void App::printDatabase() {
	Id id = 0; 
	Id step = 20;
	Database::Size max = this->database->size() - 1;
	if (!this->database) return;

	while (true) {
		App::clearScreen();
		if (!database) break;
		bool result = printDatabase(id, id + step);
		if (!result) return;

		std::wcout
			<< '\n'
			<< "{i} <id> - from <id: (0, max)>. \n"
			<< "{s} <steps> - after <steps: (0, max)> steps. \n"
			<< std::endl
			<< "{n} - next. \n"
			<< "{p} - previous. \n"
			<< "{f} - first ones. \n"
			<< "{l} - last ones. \n"
			<< "{b} - go back. \n"
			<< std::endl
			<< "Your choise: ";
		std::string answer;
		std::getline(std::cin, answer);
		char request;
		if (answer.size()) request = answer.at(0);
		else request = 'd';

		switch (request) {
		case 'p':
			id -= (id - step > 0)? step : id;
			break;

		case 'n':
			id += step;
			break;

		case 'b':
			return;
			break;

		case 'f':
			id = 0;
			break;

		case 'l':
			id = database->size() - step - 1;
			break;

		case 'i':
			if (answer.size() <= 1) break;
			if (!std::isdigit(answer.at(1))) break;
			id = std::atoi(&answer[1]);
			if (id > max) id = max;
			if (id < 0) id = 0;
			break;

		case 's':
			if (answer.size() <= 1) break;
			if (!std::isdigit(answer.at(1))) break;
			id += step * std::atoi(&answer[1]);
			if (id > max) id = max;
			if (id < 0) id = 0;
			break;

		case 'd': default:
			// .. do nothing 
			break; 
		}
	}
}

void App::print(Database* database) {
	auto temporary = this->database;
	this->database = database;
	printDatabase();
	this->database = temporary;
}

void App::print(Queue* queue) {
	Id id = 0;
	Id step = 20;
	Database::Size max = queue->size() - 1;
	if (!queue) return;
	App::clearScreen();
	Queue::Tnode *node = queue->data();

	while (node) {
		for (int i = 0; i < step; i++) {
			if (!node) break;
			print(id, node->data);
			node = node->next;
			id++;
		}
		std::wcout << '\n';

		if (node) std::wcout
			<< "{n} - next ones. \n"
			<< "{a} - show all. \n"
			<< "{b} - go back. \n";
		else std::wcout
			<< "{any} - go back. \n";
		std::wcout 
			<< std::endl
			<< "Your choise: ";
		std::string answer;
		std::getline(std::cin, answer);
		std::wcout << '\n';
		char request;
		if (answer.size()) request = answer.at(0);
		else request = 'd';

		switch (request) {
		case 'n':
			// .. next ones
			break;

		case 'a':
			step = queue->size();
			break;

		case 'b':
			return;
			break;

		case 'd': default:
			// .. do nothing 
			break;
		}
	}
	return;
}

void App::set(Database* database) {
	this->database = database;
	return;
}

App::App() {
	setlocale(LC_ALL, "rus");
	return;
}
