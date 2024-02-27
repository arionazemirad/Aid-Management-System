//Ario Nazemirad
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace sdds {
	Menu::Menu(const char* options) {
		int count = 0;

		if (options != nullptr) {
			for (int i = 0; i < (int)strlen(options) + 1; i++) {
				if (options[i] == '\t') {
					count++;
				}
			}
			if (count + 1 <= maxOptions) {
				menuContent = new char[strlen(options) + 1];
				strcpy(menuContent, options);
			}
			else {
				menuContent = nullptr;
			}
		}
		else {
			menuContent = nullptr;
		}
	}

	Menu::~Menu() {
		delete[] menuContent;
	}

	int Menu::run() const {
		int selection, i, count = 1;
		if (menuContent != nullptr) {
			cout << count << "- ";
			for (i = 0; i <= (int)strlen(menuContent); i++) {
				if (menuContent[i] == '\0') {
					cout << endl << "---------------------------------" << endl;
					cout << "0- Exit" << endl;
				}
				else if (menuContent[i] != '\t') {
					cout << menuContent[i];
				}
				else {
					cout << endl;
					cout << ++count << "- ";
				}
			}
			cout << "> ";
			selection = ut.getint(0, count);
		}
		else {
			cout << "Invalid Menu!" << endl;
			selection = 0;
		}
		return selection;
	}
}
