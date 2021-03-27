#include "Print.hpp"
using namespace Printer;
#include <string>
#include <iostream>
#include <iomanip>
using std::ios;
using std::setw;

void Printer::printRecord(Record* t) {
	std::cout.setf(ios::left);

	for (int j = 0; j < 30; j++) 
		std::cout << t->name[j];
	std::cout << setw(3) << ' ';

	for (int j = 0; j < 22; j++) 
		std::cout << t->position[j];
	std::cout << setw(3) << ' ';

	for (int j = 0; j < 10; j++)
		std::cout << t->birth[j];
	std::cout << setw(3) << ' ';

	std::cout << t->department;
	std::cout << setw(3) << ' ';
}

void Printer::printBase(const List<Data>* l, const Count rowCount) {
	for (int flag = 1; flag; flag = 1) {
		int i = 0;
		int c = 0;
		int num = 1;
		std::cout.setf(ios::left);
		system("cls");
		while (i < rowCount && num <= 4000 && l) {
			std::cout 
				<< std::setw(4) 
				<< std::setiosflags(ios::right) 
				<< std::setfill('0') 
				<< num 
				<< '.';
			std::cout.fill(' ');
			std::cout << setw(3) << ' ';
			printRecord(l->data);
			std::cout << std::endl;
			num++;
			i++;
			if (!l->next) break;
			else l = l->next;
		}
		std::cout
			<< "Show next or previous ones? \n"
			<< "Note: n - next / p - previous / b - go back \n"
			<< "Your choise: ";
		std::string answer;
		std::getline(std::cin, answer);
		char request;
		if (answer.size()) request = answer.at(0);
		else request = 'd';
		
		switch (request) {
		case 'p':
			for (int j = 0; j < rowCount * 2; j++) {
				if (l->previous) l = l->previous;
				else break;
			}
			break;
		case 'n':
			// .. do nothing ??
			break;
		case 'b':
			return;
			break;
		case 'd': default:
			for (int j = 0; j < rowCount; j++) {
				if (l->previous) l = l->previous;
				else break;
			}
		}
	}
}
