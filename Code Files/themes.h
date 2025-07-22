#pragma once

#include <iostream>
#include <cstring>
#include "utilities.h"
using namespace std;

int checker();
void theme_color(int choose);

namespace custom{
inline void theme_selector() {
	int choose;
	cout << "\n======================================\n";
	cout <<"\tTheme Selector	\n";
	cout << "======================================\n";
	cout << "1. Matrix\n";
	cout << "2. Classic CLI Theme\n";
	cout << "3. Blue Theme\n";
	cout << "4. Green Theme\n";
	cout << "5. Red and yellow Theme\n";
	cout << "6. Purple and white Theme\n";
	cout << "7. Black and Red Theme\n";
	cout << "8. Exit\n";
	cout << "===========================\n";
	do {
		cout << "Please choose a theme [1-7]: ";
		choose = checker();
		theme_color(choose);
	} while (choose != 8);
}
}
inline void theme_color(int choose) {
	switch (choose)
	{
	case 1: system("color 0A"); break;
	case 2: system("color 0F"); break;
	case 3: system("color 1E"); break;
	case 4: system("color 2F"); break;
	case 5: system("color 4E"); break;
	case 6: system("color 5F"); break;
	case 7: system("color 0B"); break;

	case 8:
		cout << "Exiting theme selector...\n";
		cin.ignore();
		return;
	}
}

inline int checker() {
	int n;
	while (true) {
		cin >> n;
		if (cin.fail() || n > 8 || n <= 0) {
			cout << "Invalid input. Please enter a number between 1 and 8: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			return n;
	}
}
