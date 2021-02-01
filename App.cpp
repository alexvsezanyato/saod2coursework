#include <fstream>
#include <iostream>
#include "DataStructs.hpp"
#include "App.hpp"
#include "Database.hpp"
#include <string>
#include <windows.h>
#include <iomanip>


void App::clearScreen() {
	system("cls");
	return;
}

void App::printMenu() {
	std::cout
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
	char result[size];
	OemToCharBuff(data, result, size);
	return result;
}

void App::print(Id id, Record* record) {
	std::cout
		<< std::setw(4)
		<< std::setfill('0')
		<< id
		<< ". ";
	std::cout << echo(record->name) << " - ";
	std::cout << echo(record->position) << " - ";
	std::cout
		<< std::setw(3)
		<< std::setfill('0')
		<< record->department
		<< " - ";
	std::cout << echo(record->birth) << '\n';
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

		std::cout
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
	Queue::Node *node = queue->data();

	while (node) {
		for (int i = 0; i < step; i++) {
			if (!node) break;
			print(id, node->data);
			node = node->next;
			id++;
		}
		std::cout << '\n';

		if (node) std::cout
			<< "{n} - next ones. \n"
			<< "{a} - show all. \n"
			<< "{b} - go back. \n";
		else std::cout
			<< "{any} - go back. \n";
		std::cout 
			<< std::endl
			<< "Your choise: ";
		std::string answer;
		std::getline(std::cin, answer);
		std::cout << '\n';
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
