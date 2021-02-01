#include "pch.h"
#include "Print.hpp"
using namespace Printer;
#include "DataStructs.hpp"
#include "Fixes.hpp"
#include <string>
#include <iostream>
#include <iomanip> // для установки кол-ва символов при выводе

void Printer::printRecord(Record* t) {
	SetConsoleCP(1251);
	std::cout.setf(ios::left);

	for (int j = 0; j < 12; j++) 
		std::cout << t->author[j];
	std::cout << setw(3) << ' ';

	for (int j = 0; j < 32; j++) 
		std::cout << t->title[j];
	std::cout << setw(3) << ' ';

	for (int j = 0; j < 16; j++)
		std::cout << t->publisher[j];
	std::cout << setw(3) << ' ';

	std::cout << t->year;
	std::cout << setw(3) << ' ';
	cout << t->pageNumber;
}

void Printer::printBase(const List* l, const Count rowCount) {
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
		SetConsoleCP(866);///Возвращаем кодировку
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

#include "Fixes.hpp"

void print_stak(queue *p) {
	list *l = p->head;
	int M = 20; ///По столько элементов выводится на экран
	int i, flag = 1, num = 1;
	int c = 0;
	while (flag) {
		i = 0;
		system("cls");
		cout << "+-----+------------+--------------------------------+----------------+------+-----+" << endl;
		while ((i < M) && (p->tail != l)) {
			cout << "|";
			cout << setw(4) << num << ")|";
			printRecord(l->data);
			cout << "+-----+------------+--------------------------------+----------------+------+-----+" << endl;
			num++;
			i++;
			if ((l->next == NULL) || (p->tail == l->next)) {
				num--;
				break;
			}
			else
				l = l->next;
		}
		SetConsoleCP(866);///Возвращаем кодировку
		c = 0;
		while ((c != 161) && (c != 27) && (c != 238)) {
			if (_kbhit()) {///Пользоавтель нажал на кнопку = 1
				c = _getch();
			}
		}
		if ((p->tail == l->next) && (c == 238)) {
			for (int j = 0; j < i - 1; j++) {
				if (l->previous == NULL) break;
				l = l->previous;
				num--;
			}
		}
		if (c == 161) {
			for (i = 0; i < 40; i++) {
				if ((l->previous == NULL) || (p->head == l)) break;
				l = l->previous;
				num--;
			}
		}
		else
			if (c == 27) {
				flag = 0;
				return;
			}
	}
}

void print_tree(vertex *&p) {
	if (p == NULL) return;
	list *tmp = p->fact;
	print_tree(p->left);
	tmp = p->fact;
	while (tmp != NULL) {
		printRecord(tmp->data);
		tmp = tmp->next;
	}
	cout << "---------------------------------------------------------------------------" << endl;
	print_tree(p->right);
}