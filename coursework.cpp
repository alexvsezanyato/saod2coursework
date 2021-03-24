#include "All.hpp"
#include "App.hpp"
#include "DataStructs.hpp"
#include "Btree-fixed.hpp"
#include "Shanon.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstring>

int main(int argc, char *argv[]) {
	// The app requires its instanse.
	App app;

	if (argc <= 1) {
		app.warning("filename required");
		return 1;
	}

	if (argc >= 2 && argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'h': {
				app.help();
				return 0;
			}

			case 'e': {
				if (argc < 3) app.warning("filename required");
				Shanon shanon;
				shanon.encode(argv[2], argv[3]);
				return 0;
			}

			case 'd': {
				if (argc < 3) app.warning("filename required");
				Shanon shanon;
				shanon.decode(argv[2], argv[3]);
				return 0;
			}

			default: {
				app.warning("wrong request");
				return 1;
			}
		}
	}

	Database database;
	char* basename = argv[1];
	bool read = database.read(basename);

	if (!read) {
		app.warning("Cannot read the file");
		return 1;
	}
	app.set(&database);
	Database* sorted = nullptr;

	Btree<Record*> tree(
        [](Record* a, Record* b) {
			auto result = a->department < b->department;
			return result;
		},
        [](Record *record) {
			std::cout << record->name << " - ";
			std::cout
				<< std::setw(3)
				<< std::setfill('0')
				<< record->department
				<< " - ";
			std::cout << record->position << " - ";
			std::cout << record->birth << '\n';
		}
    );

	while (true) {
		app.clearScreen();
		app.printMenu();
		std::wcout << std::endl;

		std::wcout << "your choise is: ";
		std::string answer;
		std::getline(std::cin, answer);
		char request;
		if (answer.size()) request = answer.at(0);
		else request = '0';

		switch (request) {
			case 'e': {
				// exit
				return 0;
			}

			case '1': {
				// just print
				app.print(&database);
				break;
			}

			case '2': {
				// print sorted data
				if (!sorted) database.copyTo(sorted);
				sorted->sort();
				app.print(sorted);
				break;
			}

			case 's': {
				// search data, sort if not sorted
				if (!sorted) database.copyTo(sorted);
				sorted->sort();
				// key = birthyear
				char key[] = "00";
				if (answer.size() != 3) break;
				if (!std::isdigit(answer.at(1))) break;
				if (!std::isdigit(answer.at(2))) break;
				key[0] = answer.at(1);
				key[1] = answer.at(2);
				Queue queue;

				sorted->search(
					Database::SearchSets{
						.searchKey = key,
						.outputTo = &queue,
					}
				);
				app.print(&queue);
				tree.make(&queue);
				app.print(&tree);
				break;
			}

			case 't': {
				if (!tree.getSize()) break;
				if (answer.size() != 4) break;
				if (!std::isdigit(answer.at(1))) break;
				if (!std::isdigit(answer.at(2))) break;
				if (!std::isdigit(answer.at(3))) break;
				answer.at(0) = '0';
				app.clearScreen();
				tree.search(std::stoi(answer));
				break;
			}
		}
	}

	// objects such as root and sorted
	// use dynamic memory allocation
	// so the memory must be freed here
	// if (root) delete root;
	if (sorted) delete sorted;
	return 0;
}
