#include "All.hpp"
#include <fstream>
#include <iostream>
#include "DataStructs.hpp"
#include "App.hpp"
#include "Database.hpp"
#include <string>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <iconv.h>

void App::clearScreen() {
	system("clear");
	return;
}

void App::print(Btree<App::Record*>* tree) {
	clearScreen();
	std::cout << "Records (last request): \n" << std::endl;
	tree->print();
	std::cout
		<< '\n'
		<< "{*} - (any key) go back. \n"
		<< "{b} - go back. \n"
		<< std::endl
		<< "Your choise: ";
	std::string answer;
	std::getline(std::cin, answer);
	char request;
	if (answer.size()) request = answer.at(0);
	else request = 'd';

	switch (request) {
	case 'b':
		// .. do nothing
		break;

	case 'd': default:
		// .. do nothing
		break;
	}
	return;
}

/*
char* echo(char* source) {
	using Conv = iconv_t;
	using Len = size_t;
	char from[] = "cp866";
	char to[] = "utf-8";

	Conv codes = iconv_open(to, from);
	if (codes == (Conv) -1) perror ("iconv_open");

	// \0 is required
	Len ilength = std::strlen(source) + 1;
	Len olength = ilength;
	char* result = new char[olength + 1];
	for (Len i = 0; i < olength; i++) result[i] = '\0';

	char* stemp = source;
	char* rtemp = result;

	Len r = iconv(
		codes,
		&stemp,
		&ilength - 1,
		&rtemp,
		&olength - 1
	);

	for (Len i = 0; i < ilength; i++)
		source[i] = '\0';

	short length = (ilength > olength)?
		olength:
		ilength;
	for (Len i = 0; i < length - 1; i++) {
		// olength must be bigger then ilength!
		source[i] = result[i];
	}

	delete [] result;
	iconv_close(codes);
	return stemp;
}
*/

void App::help() {
	std::cout
		<< "<appname> [-h, -e, -d] <filename?> <filename?>\n"
		<< "<appname> <filename>: start with the <filename> database \n"
		<< "-h: get help \n"
		<< "-e <from> <to>: encode <from> to <to> \n"
		<< "-d <from> <to>: decode <from> to <to> \n";
	return;
}

void App::warning(const char text[]) {
	std::cout
		<< "Something went wrong. \n"
		<< "Try -h for help. \n";

	if (text) {
		char* helper = new char[std::strlen(text) + 1];
		helper = std::strcpy(helper, text);
		helper[0] = std::toupper(helper[0]);
		std::cout << helper << ".\n";
		delete [] helper;
	}
	return;
}

void App::printMenu() {
	std::cout
		<< "Menu: \n"
		<< std::endl
		<< "{1}. Show records. \n"
		<< "{2}. Show sorted records. Key: birthdate. \n"
		<< std::endl
		<< "{s}. <birthyear, format: yy> Search. \n"
		<< "{t}. <deparment: number> Search by the latest result. \n"
		<< "{d}. Show the tree data. \n"
		<< "{e}. Exit \n";
	return;
}

void App::print(Record* record) {
	std::cout << record->name << " - ";
	std::cout
		<< std::setw(3)
		<< std::setfill('0')
		<< record->department
		<< " - ";
	std::cout << record->position << " - ";
	std::cout << record->birth << '\n';
}

void App::print(Id id, Record* record) {
	std::cout
		<< std::setw(4)
		<< std::setfill('0')
		<< id
		<< ". ";
	print(record);
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
		std::cout << "Records: \n" << std::endl;
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
			case 'p': {
				id -= (id - step > 0)? step : id;
				break;
			}

			case 'n': {
				id += step;
				if (id > max - 2) id = max - 2;
				break;
			}

			case 'b': {
				return;
				break;
			}

			case 'f': {
				id = 0;
				break;
			}

			case 'l': {
				id = database->size() - step - 1;
				break;
			}

			case 'i': {
				if (answer.size() <= 1) break;
				if (!std::isdigit(answer.at(1))) break;
				Id required = std::atoi(&answer[1]);
				if (required > max) break;
				if (required < 0) break;
				if (required > max - 2) required = max - 2;
				id = required;
				break;
			}

			case 's': {
				if (answer.size() <= 1) break;
				if (!std::isdigit(answer.at(1))) break;
				id += step * std::atoi(&answer[1]);
				if (id > max - 2) id = max - 2;
				if (id < 0) id = 0;
				break;
			}

			case 'd': default: {
				// .. do nothing
				break;
			}
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
		App::clearScreen();
		std::cout << "Records: \n" << std::endl;

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
