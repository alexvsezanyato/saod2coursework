#include "All.hpp"
#include "App.hpp"
#include "DataStructs.hpp"
#include <fstream>
#include <string>
#include <iomanip>


int main() {
	std::wcout.imbue(std::locale());
	std::wcin.imbue(std::locale());
	Database database;
	char basename[] = "base.dat";
	database.read(basename);
	App app;
	app.set(&database);
	Database* sorted = nullptr;
	// database::tree* root{0};

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
			case 'e': 
			{
				// exit
				return 0;
			}
			break;

			case '1':
			{
				// just print
				app.print(&database);
			}
			break;
			

			case '2': 
			{
				// print sorted data
				if (!sorted) database.copyTo(sorted);
				sorted->sort();
				app.print(sorted);
			}
			break;

			case 's':
			{
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
			}
			break;

			case 't':
			{
				// if (!root) break;
				// ..
			}
			break;
		}
	}

	// objects such as root and sorted
	// use dynamic memory allocation
	// so the memory must be freed here
	// if (root) delete root;
	if (sorted) delete sorted;
	return 0;
}
