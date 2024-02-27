/*
Name: Ario Nazemirad
Email: anazemirad@myseneca.ca
ID: 144647299
Date: Dec 3
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef MENU_H
#define MENU_H

namespace sdds {
	const int maxOptions = 15;
	class Menu {
		char* menuContent;
	public:
		Menu(const char* options = nullptr);
		~Menu();
		int run() const;
	};
}

#endif